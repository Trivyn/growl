#!/bin/bash
# Regenerate transpiled C source in csrc/ from SLOP source.
# Requires: SLOP toolchain (slop-compiler + slop Python package)
#
# Usage: ./csrc/update_bootstrap.sh

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

echo "Generating transpiled C source..."
echo ""

# 1. Transpile CLI (main entry point + all shared deps)
echo "Pass 1: CLI (main + all dependencies)"
python3 "$SCRIPT_DIR/generate_c.py" "$PROJECT_ROOT/cli" "$SCRIPT_DIR/src"
echo ""

# 2. Transpile tests in append mode (only adds test entry point)
echo "Pass 2: Tests (append mode — adds test entry only)"
python3 "$SCRIPT_DIR/generate_c.py" --append "$PROJECT_ROOT/cli/tests" "$SCRIPT_DIR/src"
echo ""

# 3. Copy runtime header
echo "Copying runtime header..."
mkdir -p "$SCRIPT_DIR/runtime"
SLOP_RUNTIME="${SLOP_HOME}/src/slop/runtime/slop_runtime.h"
if [ ! -f "$SLOP_RUNTIME" ]; then
    echo "Error: Runtime header not found at $SLOP_RUNTIME"
    echo "       Is SLOP_HOME set correctly? (currently: ${SLOP_HOME:-unset})"
    exit 1
fi
cp "$SLOP_RUNTIME" "$SCRIPT_DIR/runtime/"
echo "  Copied $SLOP_RUNTIME -> $SCRIPT_DIR/runtime/"

echo ""
echo "Done. Files in $SCRIPT_DIR/src/:"
ls "$SCRIPT_DIR/src/"*.c 2>/dev/null | wc -l | tr -d ' '
echo " .c files"
ls "$SCRIPT_DIR/src/"*.h 2>/dev/null | wc -l | tr -d ' '
echo " .h files"
