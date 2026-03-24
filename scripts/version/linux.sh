#!/bin/bash
# Usage: linux.sh [--<uapi>major|--<uapi>patchlevel|--<uapi>sublevel|--<uapi>code]
#
set -e

readonly version=$(uname -r | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true | head -1)
readonly major=${version%%.*}
readonly major_patchlevel=${version%.*}
readonly patchlevel=${major_patchlevel##*.}
readonly sublevel=${version##*.}

readonly uapi_version_h=/usr/include/linux/version.h
readonly uapicode=$(awk '/LINUX_VERSION_CODE/{print $3}' ${uapi_version_h})
readonly _uapimajor=$(awk '/LINUX_VERSION_MAJOR/{print $3}' ${uapi_version_h})
readonly _uapipatchlevel=$(awk '/LINUX_VERSION_PATCHLEVEL/{print $3}' ${uapi_version_h})
readonly _uapisublevel=$(awk '/LINUX_VERSION_SUBLEVEL/{print $3}' ${uapi_version_h})
if [[ ${_uapimajor} ]]; then
	readonly uapimajor=${_uapimajor}
else
	readonly uapimajor=$(( ${uapicode} >> 16 ))
fi
if [[ ${_uapipatchlevel} ]]; then
	readonly uapipatchlevel=${_uapipatchlevel}
else
	readonly uapipatchlevel=$(( (${uapicode} >> 8) - (${uapimajor} << 8) ))
fi
if [[ ${_uapisublevel} ]]; then
	readonly uapisublevel=${_uapisublevel}
else
	readonly uapisublevel=$(( ${uapicode} - (${uapimajor} << 16) - (${uapipatchlevel} << 8) ))
fi

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
	echo ${uapicode}
	;;
--uapimajor)
	echo ${uapimajor}
	;;
--uapipatchlevel)
	echo ${uapipatchlevel}
	;;
--uapisublevel)
	echo ${uapisublevel}
	;;
"")
	echo ${version}
	;;
*)
	exit 1
	;;
esac
