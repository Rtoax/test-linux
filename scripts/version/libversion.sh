#!/bin/bash

checkcmd() {
	local cmd=$(which ${1} 2>/dev/null || :)
	if [[ -z ${cmd} ]]; then
		echo >&2 "ERROR: not found ${cmd} in your system"
		exit 0
	fi
}

# $1: command like 'ls'
getver2() {
	checkcmd ${1}
	${1} --version | grep -Eo -e '[0-9]+\.[0-9]+' \
				  -e '[0-9]+\-[0-9]+' 2>/dev/null | \
			sort -u | \
			head -1 || true
}

# $1: command like 'ls'
getver3() {
	checkcmd ${1}
	${1} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null | \
			sort -u | \
			head -1 || true
}

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
	local seperator='.'

	TEMP=$(getopt \
		--options MmpS \
		--long major \
		--long minor \
		--long patchlevel \
		--long seperator: \
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
		-S | --seperator)
			shift
			seperator="${1}"
			shift
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

	local ver_arr=( $(echo ${version} | tr "${seperator}" ' ') )

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
