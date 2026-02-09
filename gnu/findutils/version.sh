#!/bin/bash
# This script only display findutils version, do not display other anything,
# and don't excute failed, because the git/hooks will use it.
set -e
FIND=$(which find 2>/dev/null || :)
if [[ -z ${FIND} ]]; then
	echo >&2 "ERROR: not found FIND in your system"
	exit 0
fi
${FIND} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
