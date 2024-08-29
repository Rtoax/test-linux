#!/bin/bash

find_pthread_so()
{
	local lib=
	local possible_lib=(
		/lib64/libpthread.so.0
		# Ubuntu
		/lib/x86_64-linux-gnu/libpthread.so.0
		/lib/aarch64-linux-gnu/libpthread.so.0
	)
	for c in ${possible_lib[@]}
	do
		if [[ -e $c ]]; then
			lib=$c
			break;
		fi
	done
	
	if [[ -z ${lib} ]]; then
		echo "ERROR: Not found lib.so.6" >&2
		exit 1
	fi

	echo ${lib}
}

