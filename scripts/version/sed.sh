#!/bin/bash
set -e
SED=$(which sed 2>/dev/null || :)

if [[ -z ${SED} ]]; then
	echo >&2 "ERROR: not found SED in your system"
	exit 0
fi
version=$(${SED} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
