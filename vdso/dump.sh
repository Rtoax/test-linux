#!/bin/bash
set -e

exec >&2

readonly vdso_aarch64=linux-vdso.so.1
readonly vdso_arm=linux-vdso.so.1
readonly vdso_x86_64=linux-vdso.so.1
readonly vdso_x86_32=linux-vdso.so.1

readonly pid=$$

case $(uname -m) in
x86_64) vdso_so=${vdso_x86_64} ;;
x86_32) vdso_so=${vdso_x86_32} ;;
aarch64) vdso_so=${vdso_aarch64} ;;
arm) vdso_so=${vdso_arm} ;;
esac

rm -f ${vdso_so}

readonly addr_range=( $(cat /proc/${pid}/maps \
			| grep -w '\[vdso\]' \
			| grep -o ^'[0-9a-f]*-[0-9a-f]*' \
			| tr '-' ' ')
			)
readonly vdso_sz=$(printf "%ld" $(( 0x${addr_range[1]} - 0x${addr_range[0]} )))

echo "pid ${pid} [vdso] 0x${addr_range[0]}-0x${addr_range[1]}, size = ${vdso_sz}"

dd if=/proc/${pid}/mem of=${vdso_so} \
	ibs=1 skip=$(printf %ld 0x${addr_range[0]}) \
	count=${vdso_sz}

readelf --syms --wide ${vdso_so}
# 'criu check' will check this
readelf --dynamic --wide ${vdso_so}
md5sum ${vdso_so}
