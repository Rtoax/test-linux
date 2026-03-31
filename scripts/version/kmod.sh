#!/bin/bash
set -e
MODPROBE=$(which modprobe 2>/dev/null || :)

if [[ -z ${MODPROBE} ]]; then
	echo >&2 "ERROR: not found kmod in your system"
	exit 0
fi
version=$(${MODPROBE} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
