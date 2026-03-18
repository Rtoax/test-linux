#!/bin/bash
set -e
PAHOLE=$(which pahole 2>/dev/null || :)
if [[ -z ${PAHOLE} ]]; then
	echo >&2 "ERROR: not found PAHOLE in your system"
	exit 0
fi
version=$( ${PAHOLE} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true )

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
