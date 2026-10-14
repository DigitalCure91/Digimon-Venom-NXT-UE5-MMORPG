#!/usr/bin/env python3
"""Focused source checks for previously reported C++ build failures.

This is not an Unreal compile, UHT run, or general C++ type checker. It catches
malformed ordinary literals and the specific API/access/shadowing regressions
reported by the UE 5.8 compiler. Run Unreal's actual build after these checks.
"""
from __future__ import annotations

import argparse
import re
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def mask_cpp(source: str) -> tuple[str, list[tuple[int, str]]]:
    """Hide comments/literals while retaining offsets and line breaks.

    Escaped quotes, character literals, numeric digit separators, raw strings,
    and backslash-newline continuations are recognized. This deliberately does
    not evaluate conditional preprocessing; inactive source is checked too.
    """
    masked = list(source)
    errors: list[tuple[int, str]] = []
    length = len(source)

    def hide(start: int, end: int) -> None:
        for position in range(start, end):
            if source[position] not in "\r\n":
                masked[position] = " "

    def line(position: int) -> int:
        return source.count("\n", 0, position) + 1

    index = 0
    while index < length:
        start = index
        if source.startswith("//", index):
            index += 2
            while index < length:
                if source[index] == "\\" and index + 1 < length:
                    if source[index + 1] == "\n":
                        index += 2
                        continue
                    if source.startswith("\r\n", index + 1):
                        index += 3
                        continue
                if source[index] in "\r\n":
                    break
                index += 1
            hide(start, index)
            continue
        if source.startswith("/*", index):
            end = source.find("*/", index + 2)
            if end < 0:
                errors.append((line(start), "unterminated block comment"))
                end = length - 2
            index = end + 2
            hide(start, index)
            continue
        # Match raw strings before inspecting their opening quotation mark.
        raw = re.match(r'(?:u8|u|U|L)?R"([^\s()\\]{0,16})\(', source[index:])
        if raw and (index == 0 or not (source[index - 1].isalnum() or source[index - 1] == "_")):
            ending = ")" + raw.group(1) + '"'
            end = source.find(ending, index + raw.end())
            if end < 0:
                errors.append((line(start), "unterminated raw string literal"))
                index = length
            else:
                index = end + len(ending)
            hide(start, index)
            continue
        # Consume pp-numbers so C++14 separators (1'000, 0xAB'CD) are not
        # mistaken for character-literal quotation marks.
        if source[index].isdigit() or (source[index] == "." and index + 1 < length and source[index + 1].isdigit()):
            index += 1
            while index < length:
                char = source[index]
                if char.isalnum() or char in "_.'":
                    index += 1
                elif char in "+-" and source[index - 1] in "eEpP":
                    index += 1
                else:
                    break
            continue
        if source[index] in "\"'":
            quote = source[index]
            kind = "string" if quote == '"' else "character"
            index += 1
            reported_newline = False
            closed = False
            while index < length:
                if source[index] == "\\":
                    index += 3 if source.startswith("\r\n", index + 1) else 2
                    index = min(index, length)
                    continue
                if source[index] == quote:
                    index += 1
                    closed = True
                    break
                if source[index] in "\r\n" and not reported_newline:
                    errors.append((line(start), f"unescaped newline in ordinary {kind} literal"))
                    reported_newline = True
                index += 1
            if not closed:
                errors.append((line(start), f"unterminated ordinary {kind} literal"))
            hide(start, index)
            continue
        index += 1
    return "".join(masked), errors


def closing_brace(code: str, opening: int) -> int:
    depth = 0
    for position in range(opening, len(code)):
        if code[position] == "{":
            depth += 1
        elif code[position] == "}":
            depth -= 1
            if depth == 0:
                return position
    return len(code)


def settings_include_errors(source: str, code: str) -> list[tuple[int, str]]:
    """Require the settings definition in each .cpp that uses the class.

    Unity builds can accidentally supply this include from another source file.
    Check real preprocessor lines, excluding commented-out include examples.
    This is an IWYU regression guard, not preprocessor or C++ type validation.
    """
    usage = re.search(r"\bUDigimonVenomNXTSettings\b", code)
    if not usage:
        return []
    for directive in re.finditer(r"(?m)^\s*#\s*include\b", code):
        original_line = source[directive.end():].split("\n", 1)[0]
        if re.match(r'\s*[<"]DigimonVenomNXTSettings\.h[>"]', original_line):
            return []
    return [(code.count("\n", 0, usage.start()) + 1,
             'UDigimonVenomNXTSettings requires a direct #include "DigimonVenomNXTSettings.h" (C2065/C2672)')]


def has_public_battle_query(code: str) -> bool:
    declaration = re.search(r"\bclass\s+[^;{}]*\bADigimonVenomNXTPlayerState\b[^;{}]*\{", code)
    if not declaration:
        return False
    opening = declaration.end() - 1
    body = code[opening + 1:closing_brace(code, opening)]
    token = re.compile(r"[{}]|\b(public|protected|private)\s*:|\bbool\s+HasActiveBattle\s*\(\s*\)\s*const\s*;")
    depth, access = 0, "private"
    queries: list[str] = []
    for match in token.finditer(body):
        if match.group() == "{":
            depth += 1
        elif match.group() == "}":
            depth -= 1
        elif depth == 0 and match.group(1):
            access = match.group(1)
        elif depth == 0:
            queries.append(access)
    return queries == ["public"]


def widget_slot_shadows(code: str) -> list[int]:
    """Check member definitions only, excluding namespace presentation helpers."""
    methods = re.compile(r"\bU\w+::\w+\s*\([^;{}]*\)[^{;]*\{")
    declaration = re.compile(r"\b(?P<type>[A-Za-z_]\w*(?:::\w+)*(?:\s*<[^<>;{}()]+>)?)\s*(?:[*&]\s*)*\bSlot\b\s*(?:[=;,:\[)]|\{)")
    non_types = {"return", "co_return", "throw", "delete", "case", "using", "goto"}
    positions: list[int] = []
    for method in methods.finditer(code):
        end = closing_brace(code, method.end() - 1)
        for match in declaration.finditer(code, method.start(), end):
            if match.group("type") not in non_types:
                positions.append(match.start())
    return sorted(set(positions))


def actor_role_shadows(code: str) -> list[int]:
    """Catch UE5.8 C4458 for AActor::Role in actor member definitions.

    Namespace helpers and data members such as NPC.Role remain valid.
    Input has comments and literals masked by mask_cpp.
    """
    methods = re.compile(r"\bA\w+::\w+\s*\([^;{}]*\)[^{;]*\{")
    declaration = re.compile(r"\b(?P<type>[A-Za-z_]\w*(?:::\w+)*(?:\s*<[^<>;{}()]+>)?)\s*(?:[*&]\s*)*\bRole\b\s*(?:[=;,:\[)]|\{)")
    non_types = {"return", "co_return", "throw", "delete", "case", "using", "goto"}
    positions: list[int] = []
    for method in methods.finditer(code):
        end = closing_brace(code, method.end() - 1)
        for match in declaration.finditer(code, method.start(), end):
            if match.group("type") not in non_types:
                positions.append(match.start())
    return sorted(set(positions))


def controller_member_shadows(code: str) -> list[tuple[int, str]]:
    """Catch inherited Player/Pawn hiding in controller definitions in any file.

    Includes parameters and range-for declarations. Namespace helpers may use
    these names; member access and ordinary uses are not declarations.
    Input must have comments and string literals masked with mask_cpp.
    """
    methods = re.compile(r"\bA\w*PlayerController::\w+\s*\([^;{}]*\)[^{;]*\{")
    declaration = re.compile(r"\b(?P<type>[A-Za-z_]\w*(?:::\w+)*(?:\s*<[^<>;{}()]+>)?)\s*(?:[*&]\s*)*\b(?P<member>Player|Pawn)\b\s*(?:[=;,:\[)]|\{)")
    non_types = {"return", "co_return", "throw", "delete", "case", "using", "goto"}
    positions: set[tuple[int, str]] = set()
    for method in methods.finditer(code):
        end = closing_brace(code, method.end() - 1)
        for match in declaration.finditer(code, method.start(), end):
            if match.group("type") not in non_types:
                positions.add((match.start(), match.group("member")))
    return sorted(positions)


def social_policy_imports(code: str) -> list[int]:
    """Keep role constants out of calling scopes (reported MSVC C4459).

    Qualified policy calls remain valid. A using-directive in an anonymous
    namespace also exposes Member/Leader to methods later in the translation
    unit under MSVC; pointer, record and range-for names then hide those globals.
    """
    pattern = re.compile(r"\busing\s+(?:namespace\s+DigimonVenomNXTSocialCore|DigimonVenomNXTSocialCore\s*::\s*(?:Member|Officer|Leader))\s*;")
    return [match.start() for match in pattern.finditer(code)]


def hud_panel_shadows(code: str) -> list[int]:
    """Reject HUD member locals hiding the DigimonHUDUI::Panel palette constant."""
    methods = re.compile(r"\bUDigimonVenomNXTGameHUDWidget::\w+\s*\([^;{}]*\)[^{;]*\{")
    declaration = re.compile(r"\b(?P<type>[A-Za-z_]\w*(?:::\w+)*(?:\s*<[^<>;{}()]+>)?)\s*(?:[*&]\s*)*\bPanel\b\s*(?:[=;,:\[)]|\{)")
    non_types = {"return", "co_return", "throw", "delete", "case", "using", "goto"}
    positions = set()
    for method in methods.finditer(code):
        end = closing_brace(code, method.end() - 1)
        for match in declaration.finditer(code, method.start(), end):
            if match.group("type") not in non_types:
                positions.add(match.start())
    return sorted(positions)


def external_battle_class_accesses(code: str) -> list[int]:
    """External components must use the read-only GameMode battle class accessor."""
    return [match.start() for match in re.finditer(r"(?:->|\.)\s*BattleActorClass\b", code)]


def closing_parenthesis(code: str, opening: int) -> int:
    depth = 0
    for position in range(opening, len(code)):
        if code[position] == "(":
            depth += 1
        elif code[position] == ")":
            depth -= 1
            if depth == 0:
                return position
    return len(code)


def top_level_spans(code: str, start: int, end: int):
    """Yield comma-delimited entry offsets, ignoring nested argument lists.

    Use masked C++ so commas and parentheses inside comments/literals do not
    alter the metadata boundaries.
    """
    depth, entry_start = 0, start
    for position in range(start, end):
        if code[position] in "([{":
            depth += 1
        elif code[position] in ")]}":
            depth -= 1
        elif code[position] == "," and depth == 0:
            yield entry_start, position
            entry_start = position + 1
    yield entry_start, end


def metadata_string_literal(source: str, start: int, end: int) -> str | None:
    """Read only ordinary literal metadata values, allowing surrounding comments.

    Dynamic names/expressions are not guessed. The caller has already located
    this value inside an actual reflected macro's meta=(...) argument.
    """
    parts = []
    position = start
    while position < end:
        if source[position].isspace():
            position += 1
        elif source.startswith("/*", position):
            closing = source.find("*/", position + 2, end)
            if closing < 0:
                return None
            position = closing + 2
        elif source.startswith("//", position):
            position += 2
            while position < end:
                if source.startswith("\\\r\n", position):
                    position += 3
                elif source.startswith("\\\n", position):
                    position += 2
                elif source[position] in "\r\n":
                    break
                else:
                    position += 1
        elif source[position] == '"':
            literal = re.match(r'"((?:\\(?:\r?\n|[^\r\n])|[^"\\\r\n])*)"', source[position:end])
            if not literal:
                return None
            parts.append(re.sub(r"\\\r?\n", "", literal[1]))
            position += literal.end()
        else:
            return None
    return "".join(parts) if parts else None


def class_metadata_errors(source: str, code: str | None = None) -> list[tuple[int, str]]:
    """Catch UE5.8's short class-name metadata failure before invoking UHT.

    This checks the long object-path shape, not whether a class exists. Lists
    are supported by AllowedClasses/DisallowedClasses; MetaClass/MustImplement
    name one class. Dynamic GetAllowedClasses/GetDisallowedClasses callbacks and
    unrelated metadata are intentionally excluded. Comment/string masking and
    top-level entry boundaries prevent examples or tooltips becoming metadata.
    """
    if code is None:
        code, _ = mask_cpp(source)
    errors = []
    macro_pattern = r"\b(?:UCLASS|USTRUCT|UENUM|UPROPERTY|UFUNCTION|UPARAM)\s*\("
    class_key = re.compile(r"\s*(AllowedClasses|DisallowedClasses|MetaClass|MustImplement)\s*=")
    # Permit /Script module classes and /Game or plugin Blueprint class paths.
    # Do not restrict valid package names to ASCII or assume the mount point.
    long_path = re.compile(r"/(?:[^/\s.]+/)+[^/\s.]+\.[^/\s.,]+")
    for macro in re.finditer(macro_pattern, code):
        opening = macro.end() - 1
        closing = closing_parenthesis(code, opening)
        for start, end in top_level_spans(code, opening + 1, closing):
            meta = re.match(r"\s*meta\s*=\s*\(", code[start:end])
            if not meta:
                continue
            meta_opening = start + meta.end() - 1
            meta_closing = closing_parenthesis(code, meta_opening)
            if meta_closing >= end:
                continue
            for entry_start, entry_end in top_level_spans(code, meta_opening + 1, meta_closing):
                key = class_key.match(code, entry_start, entry_end)
                if not key:
                    continue
                value = metadata_string_literal(source, key.end(), entry_end)
                if value is None:
                    continue
                values = value.split(",") if key[1] in {"AllowedClasses", "DisallowedClasses"} else [value]
                for class_name in values:
                    class_name = class_name.strip()
                    if not long_path.fullmatch(class_name):
                        line = source.count("\n", 0, key.start(1)) + 1
                        errors.append((line, f"{key[1]} class metadata value {class_name!r} must use a long object path (for example /Script/Engine.SoundBase)"))
    return errors


@dataclass(frozen=True)
class ReflectedField:
    name: str
    type_text: str
    position: int
    specifiers: str = ""


def reflected_declaration(declaration: str, position: int, specifiers: str = "") -> ReflectedField | None:
    """Read the simple field/parameter declarations used by this plugin."""
    declaration = declaration.split("=", 1)[0].strip()
    match = re.fullmatch(r"(.+?)\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*(?::\s*\d+)?", declaration, re.DOTALL)
    if not match:
        return None
    return ReflectedField(match[2], match[1].strip(), position, specifiers)


def reflected_macros(code: str, name: str):
    for match in re.finditer(r"\b" + name + r"\s*\(", code):
        opening = match.end() - 1
        closing = closing_parenthesis(code, opening)
        yield match.start(), code[opening + 1:closing], closing + 1


def reflected_properties(code: str) -> list[ReflectedField]:
    fields = []
    for position, specifiers, end in reflected_macros(code, "UPROPERTY"):
        semicolon = code.find(";", end)
        if semicolon >= 0:
            field = reflected_declaration(code[end:semicolon], position, specifiers)
            if field:
                fields.append(field)
    return fields


def split_parameters(parameters: str) -> list[str]:
    """Do not split the comma inside TMap<Key, Value> or nested templates."""
    depth, start = 0, 0
    parts = []
    for position, char in enumerate(parameters):
        if char in "<([{":
            depth += 1
        elif char in ">)]}":
            depth -= 1
        elif char == "," and depth == 0:
            parts.append(parameters[start:position])
            start = position + 1
    parts.append(parameters[start:])
    return parts


def network_container_errors(masked_files: dict[Path, str], root: Path | None = None,
                             net_serialized_structs: frozenset[str] = frozenset()) -> list[str]:
    """Catch nested map/set members that UHT rejects on the default net path.

    This follows local USTRUCT UPROPERTY fields (including array elements) from
    replicated properties and Server/Client/NetMulticast RPC parameters. It is
    deliberately not a C++ parser, UHT replacement, or ban on server-only maps.
    The optional exemption set is for explicitly reviewed custom NetSerialize
    implementations, not inferred from a method name; this plugin has none.
    """
    structs: dict[str, list[ReflectedField]] = {}
    network_roots: list[tuple[Path, str, ReflectedField]] = []
    for path, code in masked_files.items():
        for _, _, end in reflected_macros(code, "USTRUCT"):
            declaration = re.match(r"\s*struct\s+(?:\w+_API\s+)?(\w+)[^;{}]*\{", code[end:])
            if declaration:
                opening = end + declaration.end() - 1
                structs[declaration[1]] = reflected_properties(code[opening + 1:closing_brace(code, opening)])
        for field in reflected_properties(code):
            if re.search(r"\bReplicated(?:Using)?\b", field.specifiers):
                network_roots.append((path, "replicated property", field))
        for position, specifiers, end in reflected_macros(code, "UFUNCTION"):
            if not re.search(r"\b(?:Server|Client|NetMulticast)\b", specifiers):
                continue
            declaration = re.match(r"\s*[^;{}()]+?\b(\w+)\s*\(", code[end:])
            if not declaration:
                continue
            opening = end + declaration.end() - 1
            parameters = code[opening + 1:closing_parenthesis(code, opening)]
            for parameter in split_parameters(parameters):
                field = reflected_declaration(parameter, position)
                if field:
                    network_roots.append((path, f"RPC {declaration[1]} parameter", field))

    def visit(type_text: str, trail: list[str], visited: frozenset[str]):
        forbidden = re.search(r"\b(TMap|TSet)\s*<", type_text)
        if forbidden:
            yield " -> ".join(trail) + f" contains unsupported {forbidden[1]} on the default network serialization path"
            return
        for name in dict.fromkeys(re.findall(r"\b\w+\b", type_text)):
            if name not in structs or name in visited or name in net_serialized_structs:
                continue
            for member in structs[name]:
                if not re.search(r"\bNotReplicated\b", member.specifiers):
                    yield from visit(member.type_text, trail + [f"{name}.{member.name}"], visited | {name})

    errors = []
    for path, kind, field in network_roots:
        line = masked_files[path].count("\n", 0, field.position) + 1
        display_path = path.relative_to(root) if root is not None else path
        for failure in visit(field.type_text, [field.name], frozenset()):
            errors.append(f"{display_path}:{line}: {kind} {failure}")
    return errors


def validate(root: Path) -> tuple[list[str], list[str]]:
    """Return (errors, passed checks) for a plugin root containing Source/."""
    errors: list[str] = []
    checks: list[str] = []
    source_root = root / "Source"
    files = sorted(path for path in source_root.rglob("*") if path.suffix in (".h", ".cpp"))
    if not files:
        return [f"No .h/.cpp source files found under {source_root}"], []
    masked_files: dict[Path, str] = {}
    literal_errors: list[str] = []
    metadata_errors: list[str] = []
    include_errors: list[str] = []
    for path in files:
        try:
            source = path.read_text(encoding="utf-8-sig")
            code, failures = mask_cpp(source)
        except (OSError, UnicodeError) as error:
            literal_errors.append(f"{path.relative_to(root)}: cannot read source: {error}")
            continue
        masked_files[path] = code
        literal_errors.extend(f"{path.relative_to(root)}:{line}: {message}" for line, message in failures)
        metadata_errors.extend(f"{path.relative_to(root)}:{line}: {message}" for line, message in class_metadata_errors(source, code))
        if path.suffix == ".cpp":
            include_errors.extend(f"{path.relative_to(root)}:{line}: {message}" for line, message in settings_include_errors(source, code))
    if literal_errors:
        errors.extend(literal_errors)
    else:
        checks.append(f"Source literals/comments are terminated and escaped ({len(files)} C++ files)")

    if include_errors:
        errors.extend(include_errors)
    else:
        checks.append("Settings class users include its definition directly for independent translation-unit compilation")

    if metadata_errors:
        errors.extend(metadata_errors)
    else:
        checks.append("Reflected class metadata uses long object paths for AllowedClasses, DisallowedClasses, MetaClass and MustImplement")

    network_errors = network_container_errors(masked_files, root)
    if network_errors:
        errors.extend(network_errors)
    else:
        checks.append("Replicated properties and RPC struct parameters contain no unsupported TMap/TSet members")

    player_state = source_root / "DigimonVenomNXTRuntime/Public/DigimonVenomNXTPlayerState.h"
    if has_public_battle_query(masked_files.get(player_state, "")):
        checks.append("HasActiveBattle is declared once in the public PlayerState interface")
    else:
        errors.append("HasActiveBattle must be declared once as public bool HasActiveBattle() const in DigimonVenomNXTPlayerState.h")

    for pattern, success, failure in (
        (r"\bEAutomationTestFlags\s*::\s*ApplicationContextMask\b", "No unsupported ApplicationContextMask automation flag", "Unsupported EAutomationTestFlags::ApplicationContextMask"),
        (r"\bSetBrushSize\s*\(", "No deprecated UImage SetBrushSize calls", "Deprecated SetBrushSize call; use SetDesiredSizeOverride"),
    ):
        found = []
        for path, code in masked_files.items():
            for match in re.finditer(pattern, code):
                line = code.count("\n", 0, match.start()) + 1
                found.append(f"{path.relative_to(root)}:{line}: {failure}")
        if found:
            errors.extend(found)
        else:
            checks.append(success)

    # UScrollBox is the UMG wrapper; SScrollBox has a differently cased setter.
    # Scope this diagnostic to the known native UMG receiver, not valid Slate calls.
    chat_path = source_root / "DigimonVenomNXTRuntime/Private/DigimonVenomNXTWorldChatWidget.cpp"
    chat_code = masked_files.get(chat_path, "")
    wrong_scrollbar = re.search(r"\bHistoryScroll\s*->\s*SetScrollBarThickness\s*\(", chat_code)
    if wrong_scrollbar:
        line = chat_code.count("\n", 0, wrong_scrollbar.start()) + 1
        errors.append(f"{chat_path.relative_to(root)}:{line}: UScrollBox uses SetScrollbarThickness, not Slate's SetScrollBarThickness (C2039)")
    elif chat_code:
        checks.append("Native WORLD chat uses the UScrollBox scrollbar-thickness setter")

    shadows = []
    for path, code in masked_files.items():
        if path.name.endswith("Widget.cpp"):
            for position in widget_slot_shadows(code):
                line = code.count("\n", 0, position) + 1
                shadows.append(f"{path.relative_to(root)}:{line}: member-scope Slot declaration hides UWidget::Slot")
    if shadows:
        errors.extend(shadows)
    else:
        checks.append("Widget member definitions do not declare a shadowing Slot variable")
    role_shadows = []
    for path, code in masked_files.items():
        for position in actor_role_shadows(code):
            line = code.count("\n", 0, position) + 1
            role_shadows.append(f"{path.relative_to(root)}:{line}: member-scope Role declaration hides AActor::Role (C4458)")
    if role_shadows:
        errors.extend(role_shadows)
    else:
        checks.append("Actor member definitions do not declare a shadowing Role variable")
    controller_shadows = []
    for path, code in masked_files.items():
        for position, member in controller_member_shadows(code):
            line = code.count("\n", 0, position) + 1
            owner = "APlayerController" if member == "Player" else "AController"
            controller_shadows.append(f"{path.relative_to(root)}:{line}: member-scope {member} declaration hides {owner}::{member} (C4458)")
    if controller_shadows:
        errors.extend(controller_shadows)
    else:
        checks.append("PlayerController definitions across all source files do not hide inherited Player or Pawn members")
    for finder, message, passed_message, accept_path in (
        (social_policy_imports,
         "DigimonVenomNXTSocialCore role constants must stay qualified; importing Member/Leader causes C4459",
         "Social policy constants remain qualified and do not shadow local member/leader records",
         lambda path: True),
        (hud_panel_shadows,
         "HUD member-scope Panel declaration hides DigimonHUDUI::Panel (C4459)",
         "HUD member definitions do not shadow the Panel palette constant",
         lambda path: path.name == "DigimonVenomNXTGameHUDWidget.cpp"),
        (external_battle_class_accesses,
         "External access to protected GameMode BattleActorClass (C2248); use GetBattleActorClass()",
         "External callers use the public battle-class accessor instead of protected configuration",
         lambda path: path.name != "DigimonVenomNXTGameMode.cpp"),
    ):
        found = []
        for path, code in masked_files.items():
            if not accept_path(path):
                continue
            for position in finder(code):
                line = code.count("\n", 0, position) + 1
                found.append(f"{path.relative_to(root)}:{line}: {message}")
        if found:
            errors.extend(found)
        else:
            checks.append(passed_message)
    invalid_focus = []
    for path, code in masked_files.items():
        if path.name.startswith(("DigimonVenomNXTFarm", "DigimonVenomNXTFieldParty", "DigimonVenomNXTDigiLab")) and "SetIsFocusable(" in code:
            invalid_focus.append(str(path.relative_to(root)))
    if invalid_focus:
        errors.append("Native field/care buttons must initialize protected focus state in their constructor, not call unsupported SetIsFocusable: " + ", ".join(invalid_focus))
    else:
        checks.append("Native field/care buttons use UE5.8 constructor-based focus initialization")
    # These Paper2D methods are present in Editor builds but absent from the
    # packaged-game API. Keep authoring-only calls in DigimonVenomNXTEditor.
    editor_sprite_calls = []
    forbidden_sprite_api = re.compile(r"(?:->|\.)\s*(GetSourceSize|GetSourceUV|GetPivotPosition|ConvertTextureSpaceToPivotSpace|ConvertPivotSpaceToTextureSpace)\s*\(")
    for path, code in masked_files.items():
        if "DigimonVenomNXTRuntime" not in path.relative_to(source_root).parts:
            continue
        for match in forbidden_sprite_api.finditer(code):
            line = code.count("\n", 0, match.start()) + 1
            editor_sprite_calls.append(f"{path.relative_to(root)}:{line}: editor-only Paper2D API {match[1]} cannot be used by the packaged runtime")
    if editor_sprite_calls:
        errors.extend(editor_sprite_calls)
    else:
        checks.append("Runtime sprite coordinates do not call the five editor-only Paper2D APIs reported by Shipping")
    return errors, checks


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT, help="Plugin root to check (default: this script's parent plugin)")
    args = parser.parse_args()
    errors, checks = validate(args.root.resolve())
    print("C++ source regression checks only; this is not an Unreal compilation.")
    for check in checks:
        print(f"PASS: {check}")
    for error in errors:
        print(f"FAIL: {error}")
    print(f"{len(checks)} source checks passed; {len(errors)} failures.")
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
