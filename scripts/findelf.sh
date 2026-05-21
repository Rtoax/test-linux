#!/bin/bash
set -e

while read file
do
	unset bin
	read -r -N 4 bin < $file || true
	# ELF header magic
	if [[ $bin == $'\x7f'ELF* ]]; then
		echo "$file"
	fi
done <<< $(find ./ -type f)
