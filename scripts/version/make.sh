#!/bin/bash
set -e
make=$(which make 2>/dev/null || :)
if [[ -z ${make} ]]; then
	echo >&2 "ERROR: not found make in your system"
	exit 0
fi

version=$( ${make} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true )
if [[ -z ${version} ]]; then
	version=$( ${make} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true )
fi

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
