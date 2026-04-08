#!/bin/bash
readonly KiB=1024
readonly MiB=$((KiB * 1024))
readonly GiB=$((MiB * 1024))

# $1: size string, format: 123KiB, 123MB, 123B, 124KB, 123
size2bytes() {
	local size=$1
	local value=$(echo ${size} | grep -Eo '[0-9]+')

	case ${size} in
	*G | *GiB | *GB)
		echo $((${value} * ${GiB}))
		;;
	*M | *MiB | *MB)
		echo $((${value} * ${MiB}))
		;;
	*K | *KiB | *KB)
		echo $((${value} * ${KiB}))
		;;
	*B | *B | *B | *)
		echo ${value}
		;;
	esac
}

# sizealignfmt - swap size to aligned size with size KiB
# $1: size string, from 1024 to 1K
sizeceilfmt() {
	local size=${1:-0}

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
