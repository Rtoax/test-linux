#!/bin/bash
set -e
RPM=$(which rpm 2>/dev/null || :)
if [[ -z ${RPM} ]]; then
	echo >&2 "ERROR: not found RPM in your system"
	exit 0
fi
version=$(${RPM} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
