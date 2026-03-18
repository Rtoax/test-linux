#!/bin/bash
# This script only display rustc version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
RUSTC=$(which rustc 2>/dev/null || :)
if [[ -z ${RUSTC} ]]; then
	echo >&2 "ERROR: not found RUSTC in your system"
	exit 0
fi
(${RUSTC} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true ) | head -1
