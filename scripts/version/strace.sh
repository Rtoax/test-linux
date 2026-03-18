#!/bin/bash
set -e
STRACE=$(which strace 2>/dev/null || :)
if [[ -z ${STRACE} ]]; then
	echo >&2 "ERROR: not found STRACE in your system"
	exit 0
fi
version=$(${STRACE} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
