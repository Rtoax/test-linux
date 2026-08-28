#!/bin/bash
set -e

files=( "$@" )

blocksize=2048
total_size=0

[[ -z "${files}" ]] && echo "ERROR: input files" >&2 && exit 1

# $1 - block size
# $2 - size
roundup()
{
	local blksize=$1
	local size=$2
	local diff
	# Round up to block size
	diff=$(( ${size} % ${blksize} ))
	size=$(( ${size} + ${blksize} - ${diff} ))
	echo ${size}
}

for f in ${files[@]}
do
	sz=$(stat --printf %s $f)
	sz=$(roundup ${blocksize} ${sz})

	total_size=$(( ${total_size} + ${sz} ))
done

echo "Total size ${total_size} Bytes."
