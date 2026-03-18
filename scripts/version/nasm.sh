#!/bin/bash
# This script only display nasm version, do not display other anything,
# because the git/hooks will use it.
#
# Usage: nasm.sh [--major|--minor]
#
set -e
nasm=$(which nasm 2>/dev/null || :)
if [[ -z ${nasm} ]]; then
	echo >&2 "ERROR: not found nasm in your system"
	exit 0
fi

version=$( ${nasm} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]' 2>/dev/null || true )

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
