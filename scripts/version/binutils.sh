#!/bin/bash
set -e
ldbfd=$(which ld.bfd 2>/dev/null || :)
if [[ -z ${ldbfd} ]]; then
	echo >&2 "ERROR: not found binutils in your system"
	exit 0
fi

version=$( ${ldbfd} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true )

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
