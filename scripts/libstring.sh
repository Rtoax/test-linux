#!/bin/bash

# $1: size, format: 123KiB, 123MB, 123B, 124KB, 123
size2bytes() {
	local size=$1
	local value=$(echo ${size} | grep -Eo '[0-9]+')

	case ${size} in
	*G | *GiB | *GB)
		echo $((${value} * 1024 * 1024 * 1024))
		;;
	*M | *MiB | *MB)
		echo $((${value} * 1024 * 1024))
		;;
	*K | *KiB | *KB)
		echo $((${value} * 1024))
		;;
	*B | *B | *B | *)
		echo ${value}
		;;
	esac
}
