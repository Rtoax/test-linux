#!/bin/bash
set -e

libso_multi_version() {
	local name_orig=$1
	local name_v_v=$(echo ${name_orig} | grep -oE "lib[0-9a-zA-Z_\+\-]+\.so\.[0-9]+\.[0-9]+")
	local name_v=$(echo ${name_orig} | grep -oE "lib[0-9a-zA-Z_\+\-]+\.so\.[0-9]+")
	local name=$(echo ${name_orig} | grep -oE "lib[0-9a-zA-Z_\+\-]+\.so")

	if [[ ${name_orig} == ${name_v_v} ]]; then
		# Remove old symlinks first
		rm -f ${name_v} ${name}
		ln -s --force ${name_orig} ${name_v}
		ln -s --force ${name_v} ${name}
	elif [[ ${name_orig} == ${name_v} ]]; then
		rm -f ${name}
		ln -s --force ${name_orig} ${name}
	fi
}

case $1 in
multi-version)
	shift
	libso_multi_version ${1}
	;;
*)
	echo >&2 "$0: ERROR: unknown $@"
	exit 1
	;;
esac
