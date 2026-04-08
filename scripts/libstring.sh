#!/bin/bash
readonly KiB=1024
readonly MiB=$((KiB * 1024))
readonly GiB=$((MiB * 1024))

readonly LIBSTRING_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

. ${LIBSTRING_ROOT}/liblog.sh

# $1: size string, format: 123KiB, 123MB, 123B, 124KB, 123
size2bytes() {
	local size=$1

	if [[ -z ${size} ]]; then
		error "size2bytes(): Input can't be empty"
	fi

	local value=$(echo ${size} | grep -Eo '[0-9]+')
	local v2=$(echo ${size} | \
			sed 's/GiB$//g;s/GB$//g;s/G$//g' | \
			sed 's/MiB$//g;s/MB$//g;s/M$//g' | \
			sed 's/KiB$//g;s/KB$//g;s/K$//g' | \
			sed 's/$B//g')

	if [[ ${value} != ${v2} ]]; then
		error "size2bytes(): Bad format ${size}"
	fi

	case ${size:${#value}} in
	G | GiB | GB)
		echo $((${value} * ${GiB}))
		;;
	M | MiB | MB)
		echo $((${value} * ${MiB}))
		;;
	K | KiB | KB)
		echo $((${value} * ${KiB}))
		;;
	B | "")
		echo ${value}
		;;
	*)
		error "size2bytes(): Bad format ${size}"
		;;
	esac
}

# sizealignfmt - swap size to aligned size with size KiB
# $1: size string, support format: 1KiB, 1KB, 2K, so does MB,GB
sizeceilfmt() {
	local size=${1}

	size=$(size2bytes ${size})
	if [[ -z ${size} ]]; then
		error "sizeceilfmt(): Bad format ${1}"
	fi

	if (( size == 0 )); then
		echo "0B"
		return
	fi

	if (( size < ${KiB} )); then
		echo "${size}B"
		return
	elif (( size < ${MiB} )); then
		echo "$(( (size + ${KiB} - 1) / ${KiB} ))K"
		return
	elif (( size < ${GiB} )); then
		echo "$(( (size + ${MiB} - 1) / ${MiB} ))M"
		return
	else
		echo "$(( (size + ${GiB} - 1) / ${GiB} ))G"
		return
	fi
}
