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
# return: echo file type, like 'qcow2', 'unknown' if unknown or too small.
ftype() {
	local file=$1
	if [[ $(fexist ${file}) != yes ]]; then
		error "ftype: file ${file} is not exist."
	fi

	local bytes=$(stat -c "%s" ${file})
	if [[ ${bytes} -lt 8 ]]; then
		warning "ftype: ${file} is smaller than 8 B"
		echo "unknown"
		return 0
	fi

	local bin dummy
	read -r -N 8 bin < ${file}

	warning "${file} is ${bin}"

	# see also pre-commit
	case ${bin} in
	$'\x7f'ELF*)
		echo elf
		return 0
		;;
	QFI$'\xfb'*)
		echo qcow2
		return 0
		;;
	esac

	if [[ ${bytes} -ge $((512 + 8)) ]]; then
		exec 3< ${file}
		read -u 3 -N 512 dummy
		exec 3<&-
		warning "ftype: ${file} > 520 B, ${dummy}"
		case ${dummy} in
		*EFI$'\x20'PART*)
			echo "EFI-PART"
			return 0
			;;
		esac
	fi

	# TODO: add more

	echo "unknown"
	return 0
}
