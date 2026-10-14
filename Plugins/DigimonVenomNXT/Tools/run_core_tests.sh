#!/usr/bin/env bash
set -euo pipefail
plugin_root="$(cd "$(dirname "$0")/.." && pwd)"
test_tmp="$(mktemp -d)"
trap 'rm -rf "$test_tmp"' EXIT
for suite in "$plugin_root"/Tools/test_*.cpp; do
    test_name="$(basename "$suite" .cpp)"
    g++ -I"$plugin_root/Source/DigimonVenomNXTRuntime/Public" -std=c++17 -Wall -Wextra -Werror -pedantic "$suite" -o "$test_tmp/$test_name"
    "$test_tmp/$test_name"
done
