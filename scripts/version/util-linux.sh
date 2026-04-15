#!/bin/bash
set -e
GETOPT=$(which getopt 2>/dev/null || :)
if [[ -z ${GETOPT} ]]; then
	echo >&2 "ERROR: not found GETOPT in your system"
	exit 0
fi
version=$(${GETOPT} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
