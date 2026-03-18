#!/bin/bash
set -e
FIND=$(which find 2>/dev/null || :)
if [[ -z ${FIND} ]]; then
	echo >&2 "ERROR: not found FIND in your system"
	exit 0
fi
version=$(${FIND} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
