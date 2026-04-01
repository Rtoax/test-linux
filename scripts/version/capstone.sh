#!/bin/bash
set -e
CSTOOL=$(which cstool 2>/dev/null || :)
if [[ -z ${CSTOOL} ]]; then
	echo >&2 "ERROR: not found capstone in your system"
	exit 0
fi
version=$(${CSTOOL} -v | grep -Eo 'v[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version:1}
