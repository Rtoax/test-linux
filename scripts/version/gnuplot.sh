#!/bin/bash
set -e
GNUPLOT=$(which gnuplot 2>/dev/null || :)
if [[ -z ${GNUPLOT} ]]; then
	echo >&2 "ERROR: not found GNUPLOT in your system"
	exit 0
fi
version=$(${GNUPLOT} --version 2>&1 | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
