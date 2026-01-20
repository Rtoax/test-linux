#!/bin/bash
set -e

YAPF=$(which yapf 2>/dev/null || which yapf3 >/dev/null)
SRC=samples/main.py

echo "----------- yapf -----------"
${YAPF} ${SRC}
