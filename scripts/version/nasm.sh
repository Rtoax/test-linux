#!/bin/bash
set -e
nasm=$(which nasm 2>/dev/null || :)
if [[ -z ${nasm} ]]; then
	echo >&2 "ERROR: not found nasm in your system"
	exit 0
fi

version=$( ${nasm} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true )

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
