#!/bin/bash
# This script only display nasm version, do not display other anything,
# because the git/hooks will use it.
#
# Usage: version.sh [--major|--minor]
#
set -e
nasm=$(which nasm 2>/dev/null || :)
if [[ -z ${nasm} ]]; then
	echo >&2 "ERROR: not found nasm in your system"
	exit 0
fi

version=$( ${nasm} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]' 2>/dev/null || true )

case $1 in
--major)
	echo ${version%%.*} | tr -d v
	;;
--minor)
	major_minor=${version%.*}
	echo ${major_minor##*.}
	;;
--patchlevel)
	echo ${version##*.}
	;;
"")
	echo ${version}
	;;
*)
	exit 1
	;;
esac
