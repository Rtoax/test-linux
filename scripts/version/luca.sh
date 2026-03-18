#!/bin/bash
# This script only display LUCA version, do not display other anything, because
# the git/hooks will use it.
set -e
LUCA_PATH=$(readlink /opt/luca || :)
if [[ -z ${LUCA_PATH} ]]; then
	echo >&2 "ERROR: not found LUCA in your system"
	exit 0
fi
version=$(echo ${LUCA_PATH} | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
