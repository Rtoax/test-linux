#!/bin/bash

if ! [[ -e /usr/bin/bpftrace ]]; then
	exit 0
fi

libc=
possible_libc=(
	/lib64/libc.so.6
	/lib/aarch64-linux-gnu/libc.so.6
)
for c in ${possible_libc[@]}
do
	if [[ -e $c ]]; then
		libc=$c
		break;
	fi
done

if [[ -z ${libc} ]]; then
	echo "ERROR: Not found libc.so.6"
	exit 1
fi

sudo bpftrace -l usdt:${libc}:*
