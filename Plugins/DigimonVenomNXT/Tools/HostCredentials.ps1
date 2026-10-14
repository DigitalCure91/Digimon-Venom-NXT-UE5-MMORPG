# PowerShell 5.1-compatible migration of editor host credentials out of cooked config.
# No helper writes credential values to a console or a log. Assign the password getter.

function Read-DigimonCredentialDocument {
    param([Parameter(Mandatory = $true)][string]$Path)
    $Exists = [IO.File]::Exists($Path)
    $Bytes = [byte[]]@()
    $Encoding = New-Object Text.UTF8Encoding($true, $true)
    $PreambleLength = 0
    if ($Exists) {
        $Bytes = [IO.File]::ReadAllBytes($Path)
        if ($Bytes.Length -ge 4 -and (($Bytes[0] -eq 0xff -and $Bytes[1] -eq 0xfe -and $Bytes[2] -eq 0 -and $Bytes[3] -eq 0) -or
            ($Bytes[0] -eq 0 -and $Bytes[1] -eq 0 -and $Bytes[2] -eq 0xfe -and $Bytes[3] -eq 0xff))) {
            throw "Unsupported UTF-32 credential config encoding in '$Path'; no credential was changed."
        }
        if ($Bytes.Length -ge 3 -and $Bytes[0] -eq 0xef -and $Bytes[1] -eq 0xbb -and $Bytes[2] -eq 0xbf) {
            $PreambleLength = 3
        }
        elseif ($Bytes.Length -ge 2 -and $Bytes[0] -eq 0xff -and $Bytes[1] -eq 0xfe) {
            $Encoding = New-Object Text.UnicodeEncoding($false, $true, $true)
            $PreambleLength = 2
        }
        elseif ($Bytes.Length -ge 2 -and $Bytes[0] -eq 0xfe -and $Bytes[1] -eq 0xff) {
            $Encoding = New-Object Text.UnicodeEncoding($true, $true, $true)
            $PreambleLength = 2
        }
        else {
            $Encoding = New-Object Text.UTF8Encoding($false, $true)
            try { [void]$Encoding.GetString($Bytes) }
            catch {
                if ([Environment]::OSVersion.Platform -ne [PlatformID]::Win32NT) {
                    throw "Unrecognized credential config encoding in '$Path'; no credential was changed."
                }
                # WinPS/.NET Framework uses the Windows ANSI code page for legacy INIs.
                $Encoding = [Text.Encoding]::GetEncoding(0, [Text.EncoderFallback]::ExceptionFallback, [Text.DecoderFallback]::ExceptionFallback)
            }
        }
    }
    try { $Text = $Encoding.GetString($Bytes, $PreambleLength, $Bytes.Length - $PreambleLength) }
    catch { throw "Credential config encoding could not be read in '$Path'; no credential was changed." }
    return [pscustomobject]@{ Path = $Path; Exists = $Exists; Bytes = $Bytes; Encoding = $Encoding; Text = $Text }
}

function ConvertFrom-DigimonCredentialValue {
    param([AllowEmptyString()][string]$Raw)
    $Token = $Raw.Trim()
    if ($Token.IndexOf([char]0) -ge 0) { throw 'A hosting credential contains an unsupported null character; no credential was changed.' }
    if (!$Token.StartsWith('"')) { return $Token }
    $Value = New-Object Text.StringBuilder
    $Closed = $false
    for ($Index = 1; $Index -lt $Token.Length; $Index++) {
        $Character = $Token[$Index]
        if ($Character -eq '"') {
            if ($Token.Substring($Index + 1).Trim().Length -ne 0) { throw 'Ambiguous quoted hosting credential; no credential was changed.' }
            $Closed = $true
            break
        }
        if ($Character -eq '\') {
            $Index++
            if ($Index -ge $Token.Length) { throw 'Incomplete hosting credential escape; no credential was changed.' }
            switch -CaseSensitive ($Token[$Index]) {
                '\' { [void]$Value.Append('\'); break }
                '"' { [void]$Value.Append('"'); break }
                'n' { [void]$Value.Append("`n"); break }
                'r' { [void]$Value.Append("`r"); break }
                't' { [void]$Value.Append("`t"); break }
                'u' {
                    if ($Index + 4 -ge $Token.Length -or $Token.Substring($Index + 1, 4) -cnotmatch '^[0-9a-fA-F]{4}$') {
                        throw 'Invalid Unicode hosting credential escape; no credential was changed.'
                    }
                    [void]$Value.Append([char][Convert]::ToInt32($Token.Substring($Index + 1, 4), 16))
                    $Index += 4
                    break
                }
                default { throw 'Unsupported hosting credential escape; no credential was changed.' }
            }
        }
        else { [void]$Value.Append($Character) }
    }
    if (!$Closed) { throw 'Unclosed quoted hosting credential; no credential was changed.' }
    $Result = $Value.ToString()
    if ($Result.IndexOf([char]0) -ge 0) { throw 'A hosting credential contains an unsupported null character; no credential was changed.' }
    return $Result
}

function Get-DigimonCredentialEntries {
    param([Parameter(Mandatory = $true)]$Document, [switch]$Local)
    $Section = ''
    $Key = if ($Local) { 'Password' } else { 'AdminHostPassword' }
    foreach ($Line in [regex]::Matches($Document.Text, '([^\r\n]*)(?:\r\n|\r|\n|$)')) {
        if ($Line.Length -eq 0) { continue }
        $Content = $Line.Groups[1].Value
        if ($Content -match '^\s*\[([^\]]+)\]\s*$') { $Section = $Matches[1].Trim(); continue }
        if ($Content -notmatch ('^(\s*)([+.!-]?)(' + $Key + ')(\s*=\s*)(.*)$')) { continue }
        if ($Local -and $Section -ine 'Hosting') { continue }
        $Operator = $Matches[2]
        $Prefix = $Matches[1] + $Matches[3] + $Matches[4]
        $Raw = $Matches[5]
        $Value = ConvertFrom-DigimonCredentialValue -Raw $Raw
        if ($Operator.Length -ne 0) { throw "Hosting credentials use unsupported array operators in '$($Document.Path)'; no credential was changed." }
        if (!$Local -and $Value.Length -gt 0 -and $Section -ine '/Script/DigimonVenomNXTRuntime.DigimonVenomNXTSettings') {
            throw "A hosting credential is outside the Digimon settings section in '$($Document.Path)'; no credential was changed."
        }
        [pscustomobject]@{ Start = $Line.Index; Length = $Content.Length; Prefix = $Prefix; Raw = $Raw; Value = $Value; Section = $Section }
    }
}

function Get-DigimonSingleCredential {
    param([AllowEmptyCollection()][object[]]$Entries, [string]$Description)
    $Value = $null
    foreach ($Entry in $Entries) {
        if ($null -eq $Value) { $Value = [string]$Entry.Value }
        elseif (![string]::Equals($Value, [string]$Entry.Value, [StringComparison]::Ordinal)) {
            throw "Conflicting hosting credential entries in $Description; no credential was changed. Resolve the conflict without sharing the credential."
        }
    }
    if ($null -eq $Value) { return '' }
    return $Value
}

function Get-DigimonLocalHostPassword {
    param([Parameter(Mandatory = $true)][string]$ProjectFolder)
    $Document = Read-DigimonCredentialDocument -Path (Join-Path $ProjectFolder 'Saved/DigimonVenomNXT/Host.ini')
    $Entries = @(Get-DigimonCredentialEntries -Document $Document -Local)
    return Get-DigimonSingleCredential -Entries $Entries -Description 'server-local Host.ini'
}

function Test-DigimonCredentialBytes {
    param([byte[]]$First, [byte[]]$Second)
    if ($First.Length -ne $Second.Length) { return $false }
    for ($Index = 0; $Index -lt $First.Length; $Index++) { if ($First[$Index] -ne $Second[$Index]) { return $false } }
    return $true
}

function Get-DigimonCredentialBytes {
    param([Parameter(Mandatory = $true)]$Document, [AllowEmptyString()][string]$Text)
    try { return ,([byte[]]($Document.Encoding.GetPreamble() + $Document.Encoding.GetBytes($Text))) }
    catch { throw "The existing encoding cannot preserve the hosting credential in '$($Document.Path)'; no credential was changed." }
}

function Write-DigimonCredentialDocument {
    param([Parameter(Mandatory = $true)]$Document, [Parameter(Mandatory = $true)][byte[]]$Bytes)
    $Path = $Document.Path
    $Directory = [IO.Path]::GetDirectoryName($Path)
    $Temporary = Join-Path $Directory ('.digimon-host-' + [Guid]::NewGuid().ToString('N') + '.tmp')
    $Stream = $null
    try {
        [void][IO.Directory]::CreateDirectory($Directory)
        $Stream = New-Object IO.FileStream($Temporary, [IO.FileMode]::CreateNew, [IO.FileAccess]::Write, [IO.FileShare]::None)
        $Stream.Write($Bytes, 0, $Bytes.Length)
        $Stream.Flush($true)
        $Stream.Dispose()
        $Stream = $null
        if ($Document.Exists) {
            if (![IO.File]::Exists($Path) -or !(Test-DigimonCredentialBytes $Document.Bytes ([IO.File]::ReadAllBytes($Path)))) {
                throw 'Config changed during migration.'
            }
            # Ordinary $null binds as an empty string to this .NET string parameter.
            [IO.File]::Replace($Temporary, $Path, [NullString]::Value)
        }
        else { [IO.File]::Move($Temporary, $Path) }
        if (!(Test-DigimonCredentialBytes $Bytes ([IO.File]::ReadAllBytes($Path)))) { throw 'Saved config did not verify.' }
    }
    catch { throw "Could not durably save and verify '$Path'. Distributable credentials have not been removed unless already secured in Host.ini; packaging is stopped. No credential was printed." }
    finally {
        if ($null -ne $Stream) { $Stream.Dispose() }
        if ([IO.File]::Exists($Temporary)) { [IO.File]::Delete($Temporary) }
    }
}

function Move-DigimonHostCredential {
    param([Parameter(Mandatory = $true)][string]$ProjectFolder,
          [Parameter(Mandatory = $true)][string]$PluginRoot, [switch]$DryRun)
    $Documents = New-Object 'Collections.Generic.List[object]'
    $Candidate = $null
    $CandidateRaw = ''
    $SeenPaths = @{}
    foreach ($Root in @((Join-Path $ProjectFolder 'Config'), (Join-Path $PluginRoot 'Config'))) {
        if (!(Test-Path -LiteralPath $Root -PathType Container)) { continue }
        foreach ($File in @(Get-ChildItem -LiteralPath $Root -Filter '*.ini' -File -Recurse -Force | Sort-Object FullName)) {
            if ($SeenPaths.ContainsKey($File.FullName)) { continue }
            $SeenPaths[$File.FullName] = $true
            $Document = Read-DigimonCredentialDocument -Path $File.FullName
            $Entries = @(Get-DigimonCredentialEntries -Document $Document)
            if ($Entries.Count -eq 0) { continue }
            # Conflicting scalar duplicates (including a later blank) must never be guessed.
            $FileValue = Get-DigimonSingleCredential -Entries $Entries -Description "'$($File.FullName)'"
            if ($FileValue.Length -eq 0) { continue }
            if ($null -eq $Candidate) { $Candidate = $FileValue; $CandidateRaw = $Entries[0].Raw }
            elseif (![string]::Equals($Candidate, $FileValue, [StringComparison]::Ordinal)) {
                throw 'Distributable config contains different hosting credentials. No files were changed; resolve the conflict without sharing the credentials.'
            }
            $Sanitized = $Document.Text
            for ($Index = $Entries.Count - 1; $Index -ge 0; $Index--) {
                $Entry = $Entries[$Index]
                $Sanitized = $Sanitized.Remove($Entry.Start, $Entry.Length).Insert($Entry.Start, $Entry.Prefix)
            }
            $Documents.Add([pscustomobject]@{ Document = $Document; Bytes = (Get-DigimonCredentialBytes -Document $Document -Text $Sanitized) })
        }
    }
    $HostPath = Join-Path $ProjectFolder 'Saved/DigimonVenomNXT/Host.ini'
    if ($null -eq $Candidate) { return [pscustomobject]@{ Changed = $false; Planned = $false; SourceFileCount = 0; HostFile = $HostPath } }
    $HostDocument = Read-DigimonCredentialDocument -Path $HostPath
    $HostEntries = @(Get-DigimonCredentialEntries -Document $HostDocument -Local)
    $LocalValue = Get-DigimonSingleCredential -Entries $HostEntries -Description 'server-local Host.ini'
    if ($LocalValue.Length -gt 0 -and ![string]::Equals($LocalValue, $Candidate, [StringComparison]::Ordinal)) {
        throw 'The server-local Host.ini password differs from distributable config. Neither credential was changed. Resolve this conflict without sharing the credentials.'
    }
    $HostBytes = $null
    if ($LocalValue.Length -eq 0) {
        $Newline = if ($HostDocument.Text.Contains("`r`n")) { "`r`n" } elseif ($HostDocument.Text.Contains("`n")) { "`n" } elseif ($HostDocument.Text.Contains("`r")) { "`r" } else { "`r`n" }
        $HostText = $HostDocument.Text
        if ($HostEntries.Count -gt 0) {
            for ($Index = $HostEntries.Count - 1; $Index -ge 0; $Index--) {
                $Entry = $HostEntries[$Index]
                $HostText = $HostText.Remove($Entry.Start, $Entry.Length).Insert($Entry.Start, $Entry.Prefix + $CandidateRaw)
            }
        }
        else {
            if ($HostText.Length -gt 0 -and !$HostText.EndsWith("`n") -and !$HostText.EndsWith("`r")) { $HostText += $Newline }
            $HostText += '[Hosting]' + $Newline + 'Password=' + $CandidateRaw + $Newline
        }
        $HostBytes = Get-DigimonCredentialBytes -Document $HostDocument -Text $HostText
    }
    if ($DryRun) {
        Write-Host "Dry run: would preserve the hosting credential in '$HostPath' and clear it from $($Documents.Count) distributable config file(s)."
        return [pscustomobject]@{ Changed = $false; Planned = $true; SourceFileCount = $Documents.Count; HostFile = $HostPath }
    }
    # No shared-config mutation is allowed before local storage has been flushed,
    # atomically installed, reread and compared. The raw INI token remains unchanged.
    if ($null -ne $HostBytes) { Write-DigimonCredentialDocument -Document $HostDocument -Bytes $HostBytes }
    $Verified = Get-DigimonLocalHostPassword -ProjectFolder $ProjectFolder
    if (![string]::Equals($Verified, $Candidate, [StringComparison]::Ordinal)) { throw 'Local hosting credential verification failed. Distributable config was not changed.' }
    foreach ($Item in $Documents) { Write-DigimonCredentialDocument -Document $Item.Document -Bytes $Item.Bytes }
    Write-Host "Hosting credential preserved in server-local '$HostPath'; cleared from $($Documents.Count) distributable config file(s). The credential was not printed."
    return [pscustomobject]@{ Changed = $true; Planned = $false; SourceFileCount = $Documents.Count; HostFile = $HostPath }
}
