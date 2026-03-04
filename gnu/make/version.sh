#!/bin/bash
# This script only display make version, do not display other anything,
# because the git/hooks will use it.
#
# Usage: version.sh [--major|--minor]
#
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

case $1 in
--major)
	echo ${version%%.*}
	;;
--minor)
	echo ${version##*.}
	;;
"")
	echo ${version}
	;;
*)
	exit 1
	;;
esac
