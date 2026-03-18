#!/bin/bash
# This script only display lsof version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
LSOF=$(which lsof 2>/dev/null || :)
if [[ -z ${LSOF} ]]; then
	echo >&2 "ERROR: not found LSOF in your system"
	exit 0
fi
version=$(${LSOF} --version 2>&1 | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
