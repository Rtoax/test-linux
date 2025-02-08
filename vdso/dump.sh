#!/bin/bash
set -e

pid=$$
vdso_so=vdso64.so
vdso_sz=

exec >&2

readonly addr_range=( $(cat /proc/${pid}/maps \
			| grep -w '\[vdso\]' \
			| grep -o ^'[0-9a-f]*-[0-9a-f]*' \
			| tr '-' ' ')
			)
readonly vdso_sz=$(printf "%ld" $(( 0x${addr_range[1]} - 0x${addr_range[0]} )))

echo "pid ${pid} [vdso] 0x${addr_range[0]}-0x${addr_range[1]}, size = ${vdso_sz}"

dd	if=/proc/${pid}/mem \
	of=${vdso_so} \
	ibs=1 \
	skip=$(printf %ld 0x${addr_range[0]}) \
	count=${vdso_sz}

readelf --syms --wide ${vdso_so}
md5sum ${vdso_so}
