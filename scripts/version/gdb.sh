#!/bin/bash
set -e
GDB=$(which gdb 2>/dev/null || :)
if [[ -z ${GDB} ]]; then
	echo >&2 "ERROR: not found GDB in your system"
	exit 0
fi
version=$( ( ${GDB} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true ) | uniq)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
