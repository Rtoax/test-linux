#!/bin/bash
# This script only display golang version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
#
# Usage: version.sh [--major|--minor|--patchlevel]
#
set -e
GO=$(which go 2>/dev/null || :)
if [[ -z ${GO} ]]; then
	echo >&2 "ERROR: not found GO in your system"
	exit 0
fi
version=$(${GO} version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

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
