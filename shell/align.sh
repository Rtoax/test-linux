#!/bin/bash
set -e

# $1 - value
# $2 - align interval
align_up()
{
	local i
	local value=$1
	local align=$2
	local ret

	for ((i = 0;; i++))
	do
		ret=$(( $i * $align ))
		if [[ ${ret} -ge ${value} ]]; then
			break
		fi
	done

	echo ${ret}
}

align_up 3859 100
