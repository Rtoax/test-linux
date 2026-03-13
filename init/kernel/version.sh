#!/bin/bash
# This script only display kernel version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
#
# Usage: version.sh [--major|--patchlevel|--sublevel|--code]
#
set -e

version=$(uname -r | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true | head -1)
major=${version%%.*}
major_patchlevel=${version%.*}
patchlevel=${major_patchlevel##*.}
sublevel=${version##*.}

case $1 in
--major)
	echo ${major}
	;;
--patchlevel)
	echo ${patchlevel}
	;;
--sublevel)
	echo ${sublevel}
	;;
--code)
	# see /usr/include/linux/version.h
	echo $(( (${major}<<16) + (${patchlevel}<<8) + (${sublevel}>255?255:${sublevel}) ))
	;;
"")
	echo ${version}
	;;
*)
	exit 1
	;;
esac
