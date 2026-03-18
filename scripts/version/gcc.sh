#!/bin/bash
# This script only display gcc version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
#
# Usage: gcc.sh [--major|--minor|--patchlevel]
#
set -e
version=$(gcc -dumpfullversion -dumpversion)

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
