#!/bin/bash
set -ex

pid=$$
vdso_so=vdso64.so
vdso_sz=
addr_range=( $(cat /proc/${pid}/maps | grep -w '\[vdso\]' | grep -o ^'[0-9a-f]*-[0-9a-f]*' | tr '-' ' '))

echo "pid ${pid} [vdso] 0x${addr_range[0]}-0x${addr_range[1]}"

vdso_sz=$(printf "%ld" $(( 0x${addr_range[1]} - 0x${addr_range[0]} )))

echo "vdso size ${vdso_sz}"

dd if=/proc/${pid}/mem of=${vdso_so} ibs=1 iseek=$(printf %ld 0x${addr_range[0]}) count=${vdso_sz}

md5sum ${vdso_so}
