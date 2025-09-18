#!/bin/bash
set -e

while read file
do
	read -r -N 8 bin < $file
	# ELF header magic
	if [[ $bin == $'\x7f'ELF* ]]; then
		echo "$file"
	fi
done <<< $(find ./ -type f -exec file {} \; | awk -F ':' '{print $1}')
