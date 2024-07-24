#!/bin/bash
# Copyright (C) 2022-2024 CESTC, Co. All rights reserved.
#

find ./ -type f -exec file {} \; | \
	awk -F ':' '{print $1}' | \
	while read file
	do
		read -r -N 8 bin < $file
		# ELF header magic
		if [[ $bin == $'\x7f'ELF* ]]; then
			echo "$file"
		fi
	done

