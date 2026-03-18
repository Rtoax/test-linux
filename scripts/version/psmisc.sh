#!/bin/bash
# This script only display pstree version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
PSTREE=$(which pstree 2>/dev/null || :)
if [[ -z ${PSTREE} ]]; then
	echo >&2 "ERROR: not found PSTREE in your system"
	exit 0
fi
${PSTREE} --version 2>&1 | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true
