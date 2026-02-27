#!/bin/bash
# This script only display strace version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
STRACE=$(which strace 2>/dev/null || :)
if [[ -z ${STRACE} ]]; then
	echo >&2 "ERROR: not found STRACE in your system"
	exit 0
fi
${STRACE} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true
