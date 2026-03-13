#!/bin/bash
# This script only display kernel version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
#
# Usage: version.sh [--major|--minor|--patchlevel]
#
set -e

version=$(uname -r | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true | head -1)

case $1 in
--major)
	echo ${version%%.*}
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
