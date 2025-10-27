#!/bin/bash
set -e

error() {
	echo >&2 "ERROR: $@"
	exit 1
}

# $1 - symlinks, purename
# $2 - library name
# return/echo:
#   display purename if $1=purename and $2 is multiversion library name.
libso_multi_version() {
	local operate=$1
	shift
	local name_orig=$1
	local name_v_v_v=$(echo ${name_orig} | grep -oE "lib[0-9a-zA-Z_\+\-]+\.so\.[0-9]+\.[0-9]+\.[0-9]+")
	local name_v_v=$(echo ${name_orig} | grep -oE "lib[0-9a-zA-Z_\+\-]+\.so\.[0-9]+\.[0-9]+")
	local name_v=$(echo ${name_orig} | grep -oE "lib[0-9a-zA-Z_\+\-]+\.so\.[0-9]+")
	local name=$(echo ${name_orig} | grep -oE "lib[0-9a-zA-Z_\+\-]+\.so")

	case $operate in
	symlinks)
		if [[ ${name_orig} == ${name_v_v_v} ]]; then
			# Remove old symlinks first
			rm -f ${name_v_v} ${name_v} ${name}
			ln -s --force ${name_orig} ${name_v_v}
			ln -s --force ${name_v_v} ${name_v}
			ln -s --force ${name_v} ${name}
		elif [[ ${name_orig} == ${name_v_v} ]]; then
			rm -f ${name_v} ${name}
			ln -s --force ${name_orig} ${name_v}
			ln -s --force ${name_v} ${name}
		elif [[ ${name_orig} == ${name_v} ]]; then
			rm -f ${name}
			ln -s --force ${name_orig} ${name}
		elif [[ ${name_orig} == ${name} ]]; then
			return 0
		else
			error "not support format ${name_orig}"
		fi
		;;
	purename)
		if [[ ${name_orig} == ${name_v_v_v} ]] ||
		   [[ ${name_orig} == ${name_v_v} ]] ||
		   [[ ${name_orig} == ${name_v} ]]; then
			echo ${name}
		else
			return 0
		fi
		;;
	*)
		error "not support operate ${operate}"
	esac
}

case $1 in
multi-version)
	shift
	libso_multi_version symlinks ${1}
	;;
# For example:
# input:  liba.so.1 libb.so.2 libc.so
# output: liba.so libb.so
multi-version-pure-name-list)
	shift
	declare -a namelist
	for so in ${@}
	do
		namelist+=( $(libso_multi_version purename ${so}) )
	done
	echo ${namelist[@]}
	;;
*)
	error "$0: unknown parameter $@"
	;;
esac
