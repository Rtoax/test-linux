#!/bin/bash
# This script only display binutils version, do not display other anything,
# because the git/hooks will use it.
#
# Usage: binutils.sh [--major|--minor]
#
set -e
ldbfd=$(which ld.bfd 2>/dev/null || :)
if [[ -z ${ldbfd} ]]; then
	echo >&2 "ERROR: not found binutils in your system"
	exit 0
fi

version=$( ${ldbfd} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true )

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
