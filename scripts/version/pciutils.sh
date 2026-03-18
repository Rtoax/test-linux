#!/bin/bash
set -e
LSPCI=$(which lspci 2>/dev/null || :)
if [[ -z ${LSPCI} ]]; then
	echo >&2 "ERROR: not found LSPCI in your system"
	exit 0
fi
version=$(${LSPCI} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
