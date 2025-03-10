#!/bin/bash
set -e

read_hex_from_file() {
	local file=$1
	local off=$2
	local bytes=$3

	local tmp=$(mktemp -u tmp-XXX.bin)
	dd if=${file} skip=$(printf %ld ${off}) ibs=1 of=${tmp} count=${bytes} 2>/dev/null
	# Remove prefix $1
	local vals=( $(od -tx${bytes} ${tmp} | awk '{print $2}') )
	echo 0x${vals[0]}
	rm -f ${tmp}
}

# Test
if [[ $# -ge 1 ]]; then
	FILE=/usr/bin/ls

	# Get '\x7f'ELF
	read_hex_from_file ${FILE} 0x0 4
fi
