#!/usr/bin/env bash
# Formats (or checks) all project C++ sources with clang-format.
#
# Usage:
#   scripts/format.sh          # format all files in place
#   scripts/format.sh --check  # fail if any file is not formatted (used by CI)

set -eo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

if ! command -v clang-format >/dev/null 2>&1; then
    echo "error: clang-format is not installed or not on PATH" >&2
    exit 1
fi

mapfile -d '' FILES < <(find modules app tests \
    -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) -print0)

if [[ ${#FILES[@]} -eq 0 ]]; then
    echo "No C++ files found to format."
    exit 0
fi

if [[ "$1" == "--check" ]]; then
    clang-format --dry-run --Werror "${FILES[@]}"
    echo "All files are formatted correctly."
else
    clang-format -i "${FILES[@]}"
    echo "Formatted ${#FILES[@]} file(s)."
fi
