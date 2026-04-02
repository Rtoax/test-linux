#!/bin/bash
set -e
OPENSSL=$(which openssl 2>/dev/null || :)
if [[ -z ${OPENSSL} ]]; then
	echo >&2 "ERROR: not found OPENSSL in your system"
	exit 0
fi
version=$((${OPENSSL} --version 2>/dev/null | ${OPENSSL} version 2>/dev/null) | \
		grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' | head -1)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
