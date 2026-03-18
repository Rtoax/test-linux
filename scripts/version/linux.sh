#!/bin/bash
# Usage: linux.sh [--<uapi>major|--<uapi>patchlevel|--<uapi>sublevel|--<uapi>code]
#
set -e

readonly version=$(uname -r | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true | head -1)
readonly major=${version%%.*}
readonly major_patchlevel=${version%.*}
readonly patchlevel=${major_patchlevel##*.}
readonly sublevel=${version##*.}

readonly version_h=/usr/include/linux/version.h

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
--uapicode)
	echo $(awk '/LINUX_VERSION_CODE/{print $3}' ${version_h})
	;;
--uapimajor)
	echo $(awk '/LINUX_VERSION_MAJOR/{print $3}' ${version_h})
	;;
--uapipatchlevel)
	echo $(awk '/LINUX_VERSION_PATCHLEVEL/{print $3}' ${version_h})
	;;
--uapisublevel)
	echo $(awk '/LINUX_VERSION_SUBLEVEL/{print $3}' ${version_h})
	;;
"")
	echo ${version}
	;;
*)
	exit 1
	;;
esac
