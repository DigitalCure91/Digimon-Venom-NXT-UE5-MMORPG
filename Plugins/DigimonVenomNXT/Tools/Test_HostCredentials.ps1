# Real filesystem fixtures; no Unreal installation or real credential is used.
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version 2.0
. (Join-Path $PSScriptRoot 'HostCredentials.ps1')
. (Join-Path $PSScriptRoot 'NativeBuildChecks.ps1')
$FixtureRoot = Join-Path ([IO.Path]::GetTempPath()) ('DigimonHostCredentials-' + [Guid]::NewGuid().ToString('N'))
$Passed = 0
$Section = '[/Script/DigimonVenomNXTRuntime.DigimonVenomNXTSettings]'

function Assert-Fixture {
    param([bool]$Condition, [string]$Message)
    if (!$Condition) { throw $Message }
}
function Assert-FixtureThrows {
    param([scriptblock]$Action, [string]$Pattern)
    $Thrown = $false
    try { & $Action | Out-Null }
    catch { $Thrown = $true; Assert-Fixture ($_.Exception.Message -match $Pattern) 'Unexpected exception category.' }
    Assert-Fixture $Thrown 'An unsafe operation unexpectedly succeeded.'
}
function New-CredentialFixture {
    $Project = Join-Path $FixtureRoot ([Guid]::NewGuid().ToString('N'))
    $Plugin = Join-Path $Project 'Plugins/DigimonVenomNXT'
    [void][IO.Directory]::CreateDirectory((Join-Path $Project 'Config'))
    [void][IO.Directory]::CreateDirectory((Join-Path $Plugin 'Config'))
    return [pscustomobject]@{ Project = $Project; Plugin = $Plugin; Config = (Join-Path $Project 'Config/DefaultGame.ini'); Local = (Join-Path $Project 'Saved/DigimonVenomNXT/Host.ini') }
}
function Write-FixtureText {
    param([string]$Path, [string]$Text, $Encoding = (New-Object Text.UTF8Encoding($false, $true)))
    [void][IO.Directory]::CreateDirectory([IO.Path]::GetDirectoryName($Path))
    [IO.File]::WriteAllText($Path, $Text, $Encoding)
}
function Move-FixtureCredential {
    param($Fixture, [switch]$DryRun)
    Move-DigimonHostCredential -ProjectFolder $Fixture.Project -PluginRoot $Fixture.Plugin -DryRun:$DryRun
}
function Test-CredentialFixture {
    param([string]$Name, [scriptblock]$Body)
    & $Body
    $script:Passed++
    Write-Host "PASS $Name"
}

try {
    Test-CredentialFixture 'ordinary migration preserves settings, local password, postcondition and no secret log' {
        $F = New-CredentialFixture
        $Secret = 'fixture-only-Alpha!42'
        Write-FixtureText $F.Config ($Section + "`r`nPublicGameAddress=127.0.0.1`r`nAdminHostPassword=" + $Secret + "`r`nMaxPlayers=12`r`n")
        $Output = @(Move-FixtureCredential $F 6>&1)
        Assert-Fixture ((Get-DigimonLocalHostPassword $F.Project) -ceq $Secret) 'Migrated password differs.'
        Assert-Fixture ([IO.File]::ReadAllText($F.Config) -ceq ($Section + "`r`nPublicGameAddress=127.0.0.1`r`nAdminHostPassword=`r`nMaxPlayers=12`r`n")) 'Unrelated config or newlines changed.'
        Assert-Fixture (($Output | Out-String) -notlike ('*' + $Secret + '*')) 'Credential was logged.'
        Assert-DigimonNoSharedHostSecret -ProjectFolder $F.Project -PluginRoot $F.Plugin
    }
    Test-CredentialFixture 'matching project and plugin duplicates migrate together' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=fixture-dupe`nAdminHostPassword=""fixture-dupe""`n")
        $Other = Join-Path $F.Plugin 'Config/DefaultDigimonVenomNXT.ini'
        Write-FixtureText $Other ($Section + "`nAdminHostPassword=fixture-dupe`n")
        $Result = Move-FixtureCredential $F
        Assert-Fixture ($Result.SourceFileCount -eq 2) 'Duplicate file count differs.'
        Assert-DigimonNoSharedHostSecret -ProjectFolder $F.Project -PluginRoot $F.Plugin
    }
    Test-CredentialFixture 'different distributable credentials abort without creating Saved' {
        $F = New-CredentialFixture
        $Before = $Section + "`nAdminHostPassword=fixture-first`n"
        Write-FixtureText $F.Config $Before
        Write-FixtureText (Join-Path $F.Plugin 'Config/DefaultDigimonVenomNXT.ini') ($Section + "`nAdminHostPassword=fixture-second`n")
        Assert-FixtureThrows { Move-FixtureCredential $F } 'different hosting credentials'
        Assert-Fixture ([IO.File]::ReadAllText($F.Config) -ceq $Before) 'Source changed on conflict.'
        Assert-Fixture (!(Test-Path (Join-Path $F.Project 'Saved'))) 'Conflict created local files.'
    }
    Test-CredentialFixture 'differing local password aborts without touching either file' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=fixture-source`n")
        Write-FixtureText $F.Local "[Hosting]`nPassword=fixture-local`nPort=7777`n"
        $Source = [IO.File]::ReadAllBytes($F.Config); $Local = [IO.File]::ReadAllBytes($F.Local)
        Assert-FixtureThrows { Move-FixtureCredential $F } 'password differs'
        Assert-Fixture (Test-DigimonCredentialBytes $Source ([IO.File]::ReadAllBytes($F.Config))) 'Source changed on conflict.'
        Assert-Fixture (Test-DigimonCredentialBytes $Local ([IO.File]::ReadAllBytes($F.Local))) 'Local changed on conflict.'
    }
    Test-CredentialFixture 'matching existing local file stays byte-identical' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=fixture-match`n")
        Write-FixtureText $F.Local "; existing operator note`n[Hosting]`nPassword=""fixture-match""`nPort=9000`n[Other]`nPassword=unrelated`n"
        $Before = [IO.File]::ReadAllBytes($F.Local)
        Move-FixtureCredential $F | Out-Null
        Assert-Fixture (Test-DigimonCredentialBytes $Before ([IO.File]::ReadAllBytes($F.Local))) 'Existing local settings were rewritten.'
    }
    Test-CredentialFixture 'blank local password is filled without changing other settings' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=fixture-fill`n")
        Write-FixtureText $F.Local "[Hosting]`nPassword=`nPort=8111`n[Other]`nKey=KeepMe"
        Move-FixtureCredential $F | Out-Null
        Assert-Fixture ([IO.File]::ReadAllText($F.Local) -ceq "[Hosting]`nPassword=fixture-fill`nPort=8111`n[Other]`nKey=KeepMe") 'Local unrelated settings changed.'
    }
    Test-CredentialFixture 'missing local key appends Hosting section without changing existing bytes' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=fixture-append`n")
        $Original = "[Hosting]`nPort=8111`n[Other]`nKey=KeepMe"
        Write-FixtureText $F.Local $Original
        Move-FixtureCredential $F | Out-Null
        Assert-Fixture ([IO.File]::ReadAllText($F.Local).StartsWith($Original + "`n[Hosting]`nPassword=fixture-append`n")) 'Existing host content changed.'
    }
    Test-CredentialFixture 'dry run leaves every byte and directory unchanged' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=fixture-dry`n")
        $Before = [IO.File]::ReadAllBytes($F.Config)
        $Result = Move-FixtureCredential $F -DryRun
        Assert-Fixture ($Result.Planned -and !$Result.Changed) 'Dry-run result differs.'
        Assert-Fixture (Test-DigimonCredentialBytes $Before ([IO.File]::ReadAllBytes($F.Config))) 'Dry run wrote source.'
        Assert-Fixture (!(Test-Path (Join-Path $F.Project 'Saved'))) 'Dry run created Saved.'
    }
    Test-CredentialFixture 'idempotent repeat changes neither source nor local file' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=fixture-repeat`n")
        Move-FixtureCredential $F | Out-Null
        $Source = [IO.File]::ReadAllBytes($F.Config); $Local = [IO.File]::ReadAllBytes($F.Local)
        $Result = Move-FixtureCredential $F
        Assert-Fixture (!$Result.Changed -and !$Result.Planned) 'Repeat was not a no-op.'
        Assert-Fixture (Test-DigimonCredentialBytes $Source ([IO.File]::ReadAllBytes($F.Config))) 'Repeat changed source.'
        Assert-Fixture (Test-DigimonCredentialBytes $Local ([IO.File]::ReadAllBytes($F.Local))) 'Repeat changed local.'
    }
    foreach ($EncodingName in @('UTF8', 'UTF8BOM', 'UTF16LE', 'UTF16BE')) {
        Test-CredentialFixture ("encoding and Unicode preservation: " + $EncodingName) {
            $F = New-CredentialFixture
            $Encoding = switch ($EncodingName) {
                'UTF8' { New-Object Text.UTF8Encoding($false, $true) }
                'UTF8BOM' { New-Object Text.UTF8Encoding($true, $true) }
                'UTF16LE' { New-Object Text.UnicodeEncoding($false, $true, $true) }
                'UTF16BE' { New-Object Text.UnicodeEncoding($true, $true, $true) }
            }
            $Unicode = 'fixture-' + [char]0x00e9 + [char]0x5317
            Write-FixtureText $F.Config ($Section + "`r`n; note " + $Unicode + "`r`nAdminHostPassword=" + $Unicode + "`r`nOther=Stay`r`n") $Encoding
            Write-FixtureText $F.Local "[Hosting]`r`nPassword=`r`nOther=Keep`r`n" $Encoding
            Move-FixtureCredential $F | Out-Null
            Assert-Fixture ((Get-DigimonLocalHostPassword $F.Project) -ceq $Unicode) 'Unicode credential differs.'
            $Expected = $Section + "`r`n; note " + $Unicode + "`r`nAdminHostPassword=`r`nOther=Stay`r`n"
            Assert-Fixture (Test-DigimonCredentialBytes ([byte[]]($Encoding.GetPreamble() + $Encoding.GetBytes($Expected))) ([IO.File]::ReadAllBytes($F.Config))) 'Config encoding or content changed.'
            Assert-Fixture ((Read-DigimonCredentialDocument $F.Local).Encoding.CodePage -eq $Encoding.CodePage) 'Local encoding changed.'
        }
    }
    Test-CredentialFixture 'quoted escapes and symbols preserve raw token and decoded password' {
        $F = New-CredentialFixture
        $Raw = '"fixture \"quote\" \\ \u5317 \t %!;#=$()"'
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=" + $Raw + "`n")
        Move-FixtureCredential $F | Out-Null
        $Expected = 'fixture "quote" \ ' + [char]0x5317 + " `t %!;#=`$()"
        Assert-Fixture ((Get-DigimonLocalHostPassword $F.Project) -ceq $Expected) 'Escape decoding differs.'
        Assert-Fixture ([IO.File]::ReadAllText($F.Local).Contains('Password=' + $Raw)) 'Raw INI escape representation changed.'
    }
    Test-CredentialFixture 'literal unquoted backslashes and inline semicolon remain literal' {
        $F = New-CredentialFixture
        $Secret = 'fixture\folder;this-is-part-of-the-value#too'
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=" + $Secret + "`n")
        Move-FixtureCredential $F | Out-Null
        Assert-Fixture ((Get-DigimonLocalHostPassword $F.Project) -ceq $Secret) 'Literal characters changed.'
    }
    Test-CredentialFixture 'whitespace password is retained instead of treated as empty' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=""  ""`n")
        Move-FixtureCredential $F | Out-Null
        Assert-Fixture ((Get-DigimonLocalHostPassword $F.Project) -ceq '  ') 'Significant whitespace was lost.'
    }
    Test-CredentialFixture 'commented credentials are not moved or removed' {
        $F = New-CredentialFixture
        $Original = $Section + "`n; AdminHostPassword=comment-only`nAdminHostPassword=""""`n"
        Write-FixtureText $F.Config $Original
        $Result = Move-FixtureCredential $F
        Assert-Fixture (!$Result.Changed -and [IO.File]::ReadAllText($F.Config) -ceq $Original) 'Comment or empty key changed.'
        Assert-Fixture (!(Test-Path $F.Local)) 'An empty config created a credential.'
    }
    Test-CredentialFixture 'conflicting repeated local keys fail without source changes' {
        $F = New-CredentialFixture
        $Original = $Section + "`nAdminHostPassword=fixture-first`n"
        Write-FixtureText $F.Config $Original
        Write-FixtureText $F.Local "[Hosting]`nPassword=fixture-first`nPassword=fixture-second`n"
        Assert-FixtureThrows { Move-FixtureCredential $F } 'Conflicting hosting credential'
        Assert-Fixture ([IO.File]::ReadAllText($F.Config) -ceq $Original) 'Source changed on local duplicates.'
    }
    Test-CredentialFixture 'a later blank duplicate cannot silently change effective behavior' {
        $F = New-CredentialFixture
        $Original = $Section + "`nAdminHostPassword=fixture-value`nAdminHostPassword=`n"
        Write-FixtureText $F.Config $Original
        Assert-FixtureThrows { Move-FixtureCredential $F } 'Conflicting hosting credential'
        Assert-Fixture ([IO.File]::ReadAllText($F.Config) -ceq $Original) 'Conflicting duplicate changed.'
    }
    Test-CredentialFixture 'local save failure never removes distributable credential' {
        $F = New-CredentialFixture
        $Original = $Section + "`nAdminHostPassword=fixture-write-failure`n"
        Write-FixtureText $F.Config $Original
        Write-FixtureText (Join-Path $F.Project 'Saved') 'A file blocks directory creation.'
        Assert-FixtureThrows { Move-FixtureCredential $F } 'Could not durably save'
        Assert-Fixture ([IO.File]::ReadAllText($F.Config) -ceq $Original) 'Source stripped before durable save.'
    }
    Test-CredentialFixture 'concurrent file edits are not overwritten and temporary files are removed' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config 'original'
        $Document = Read-DigimonCredentialDocument $F.Config
        $Bytes = Get-DigimonCredentialBytes $Document 'planned'
        Write-FixtureText $F.Config 'concurrently changed'
        Assert-FixtureThrows { Write-DigimonCredentialDocument $Document $Bytes } 'Could not durably save'
        Assert-Fixture ([IO.File]::ReadAllText($F.Config) -ceq 'concurrently changed') 'Concurrent changes overwritten.'
        Assert-Fixture (@(Get-ChildItem (Split-Path $F.Config) -Filter '*.tmp' -Force).Count -eq 0) 'Temporary credential file left behind.'
    }
    Test-CredentialFixture 'unexpected section and unsupported escape stop before changes' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config "[Unrelated]`nAdminHostPassword=fixture-other`n"
        Assert-FixtureThrows { Move-FixtureCredential $F } 'outside the Digimon settings section'
        Write-FixtureText $F.Config ($Section + "`n" + 'AdminHostPassword="fixture\q"')
        Assert-FixtureThrows { Move-FixtureCredential $F } 'Unsupported hosting credential escape'
        Assert-Fixture (!(Test-Path $F.Local)) 'Malformed source created a credential.'
    }
    Test-CredentialFixture 'migration leaves environment override untouched' {
        $F = New-CredentialFixture
        Write-FixtureText $F.Config ($Section + "`nAdminHostPassword=fixture-persistent`n")
        $Previous = [Environment]::GetEnvironmentVariable('DIGIMONVENOMNXT_HOST_PASSWORD', 'Process')
        try {
            [Environment]::SetEnvironmentVariable('DIGIMONVENOMNXT_HOST_PASSWORD', 'fixture-environment', 'Process')
            Move-FixtureCredential $F | Out-Null
            Assert-Fixture ($env:DIGIMONVENOMNXT_HOST_PASSWORD -ceq 'fixture-environment') 'Environment precedence was modified.'
            Assert-Fixture ((Get-DigimonLocalHostPassword $F.Project) -ceq 'fixture-persistent') 'Persistent fallback was not preserved.'
        }
        finally { [Environment]::SetEnvironmentVariable('DIGIMONVENOMNXT_HOST_PASSWORD', $Previous, 'Process') }
    }
    Write-Host "$Passed hosting credential migration fixtures passed."
}
finally { if ([IO.Directory]::Exists($FixtureRoot)) { [IO.Directory]::Delete($FixtureRoot, $true) } }
