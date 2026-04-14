#!/bin/bash
if [[ -z ${KiB} ]]; then
	readonly KiB=1024
	readonly MiB=$((KiB * 1024))
	readonly GiB=$((MiB * 1024))
fi

if [[ -z ${LIBSTRING_ROOT} ]]; then
	readonly LIBSTRING_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))
fi

. ${LIBSTRING_ROOT}/liblog.sh

# size2bytes - swap size to bytes
# $1: size string, format: 123KiB, 123MB, 123B, 124KB, 123
# return: echo Bytes size without 'B' suffix
#         empty if failed, 0 if nothing input
size2bytes() {
	local size=$1

	if [[ -z ${size} ]]; then
		echo 0
		return
	fi

	local value=$(echo ${size} | grep -Eo '[0-9]+')
	local v2=$(echo ${size} | \
			sed 's/GiB$//g;s/GB$//g;s/G$//g' | \
			sed 's/MiB$//g;s/MB$//g;s/M$//g' | \
			sed 's/KiB$//g;s/KB$//g;s/K$//g' | \
			sed 's/B$//g')

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

# sizechkalign - check size alignement
# $1: input size
# $2: align size
# return: echo 'y' if align, 'n' if not align, empty if failed
sizechkalign() {
	local input=$1
	local align=$2

	[[ -z ${input} ]] && error "sizechkalign(): need input on 1st arg"
	[[ -z ${align} ]] && error "sizechkalign(): need align on 2nd arg"

	local s_input=$(size2bytes ${input})
	local s_align=$(size2bytes ${align})

	if [[ ${s_align} -eq 0 ]]; then
		error "sizechkalign(): division by 0 in ${align}"
	fi

	local mod_remainder=$((s_input % s_align))
	if [[ ${mod_remainder} -eq 0 ]]; then
		echo 'y'
		return
	else
		echo 'n'
		return
	fi
}

# sizeceilfmt - swap size to aligned size with size KiB
# $1: size string, support format: 1KiB, 1KB, 2K, so does MB,GB
# return: echo format size, empty if failed
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

# sizesum - calculate size sum
# $@: each one is 1KiB, 1KB
# return: echo Bytes of size, empty if failed
sizesum() {
	local sumB=0

	for s in ${@}
	do
		local b=$(size2bytes ${s})
		sumB=$(( sumB + b ))
	done

	echo ${sumB:+${sumB}B}
}
