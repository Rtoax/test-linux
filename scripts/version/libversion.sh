#!/bin/bash

version_parser_usage()
{
	echo -e "
--major
--minor
--patchlevel
" | more
	exit ${1-0}
}

# version string format: MAJOR.MINOR.PATCHLEVEL or MAJOR.MINOR
version_parser() {
	local show_major show_minor show_patchlevel show_whole=YES
	local version

	TEMP=$(getopt \
		--options Mmp \
		--long major \
		--long minor \
		--long patchlevel \
		-n version-parser -- "$@")

	test $? != 0 && version_parser_usage 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-M | --major)
			shift
			show_major=YES
			show_whole=
			;;
		-m | --minor)
			shift
			show_minor=YES
			show_whole=
			;;
		-p | --patchlevel)
			shift
			show_patchlevel=YES
			show_whole=
			;;
		--)
			shift
			version="$1"
			break
			;;
		*)
			echo >&2 "ERROR: unknown ${1}"
			exit 1
			;;
		esac
	done

	local ver_arr=( $(echo ${version} | tr '.' ' ') )

	[[ ${show_major} ]] && echo ${ver_arr[0]}
	[[ ${show_minor} ]] && echo ${ver_arr[1]}
	[[ ${show_patchlevel} ]] && echo ${ver_arr[2]}
	[[ ${show_whole} ]] && echo ${version}
	return 0
}

# $1: library name, like libbpf.so, libxdp.so
ldconfig_libver()
{
	# Opensuse has /sbin/ldconfig.
	LDCONFIG=$(which ldconfig 2>/dev/null || ls /sbin/ldconfig 2>/dev/null)
	realpath $(${LDCONFIG} -p | grep ${1} 2>/dev/null | \
			awk '{print $NF}' | \
			head -1 || :) 2>/dev/null || :
}
