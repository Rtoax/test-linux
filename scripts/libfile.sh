#!/bin/bash

if [[ -z ${LIBFILE_ROOT} ]]; then
	readonly LIBFILE_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))
fi

. ${LIBFILE_ROOT}/liblog.sh

# $1: input file
# return: echo 'yes' if exist, 'no' if not exist
fexist() {
	local file=$1
	if [[ -z ${file} ]]; then
		error "fexist: must input file"
	fi
	if [[ -e ${file} ]]; then
		echo yes
	else
		echo no
	fi
}

# $1: input file
# return: echo file type, like 'qcow2'
ftype() {
	local file=$1
	if [[ $(fexist ${file}) != yes ]]; then
		error "ftype: file ${file} is not exist."
	fi

	local bin
	read -r -N 8 bin < ${file}
	if [[ ${bin} == $'\x7f'ELF* ]]; then
		echo elf
		return 0
	fi

	if [[ "$(file ${file})" =~ "QCOW2" ]]; then
		echo qcow2
	fi

	# TODO: add more

	return 0
}
