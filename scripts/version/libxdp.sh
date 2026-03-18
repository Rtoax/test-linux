#!/bin/bash
# This script only display LIBXDP version, do not display other anything,
# because the git/hooks will use it.
set -e

LIBXDP_PATH=$(realpath $(ldconfig -p | \
				grep libxdp.so 2>/dev/null | \
				awk '{print $NF}' | \
				head -1) 2>/dev/null \
		|| :)

if [[ -z ${LIBXDP_PATH} ]]; then
	echo >&2 "ERROR: not found libxdp.so in anywhere"
	exit 1
fi

version=$(echo ${LIBXDP_PATH} | \
		grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

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
