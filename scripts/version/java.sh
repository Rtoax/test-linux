#!/bin/bash
set -e
JAVAC=$(which javac 2>/dev/null || :)
if [[ -z ${JAVAC} ]]; then
	echo >&2 "ERROR: not found JAVAC in your system"
	exit 0
fi
version=$(${JAVAC} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
