#!/bin/bash
# This script only display make version, do not display other anything,
# because the git/hooks will use it.
set -e
make=$(which make 2>/dev/null || :)
if [[ -z ${make} ]]; then
	echo >&2 "ERROR: not found make in your system"
	exit 0
fi
${make} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
