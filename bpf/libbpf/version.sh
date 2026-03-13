#!/bin/bash
# This script only display LIBBPF version, do not display other anything,
# because the git/hooks will use it.
set -e

LIBBPF_PATH=$(realpath $(ldconfig -p | \
				grep libbpf.so 2>/dev/null | \
				awk '{print $NF}' | \
				head -1) 2>/dev/null \
		|| :)

if [[ -z ${LIBBPF_PATH} ]]; then
	echo >&2 "ERROR: not found libbpf.so in anywhere"
	exit 1
fi

version=$(echo ${LIBBPF_PATH} | \
		grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

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
