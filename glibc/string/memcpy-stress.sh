#!/bin/bash
set -e

readonly MiB=1024*1024

make memcpy-stress

pfx=
exe=memcpy-stress
firstline=YES
msize_MB=1024*4

[[ $1 ]] && exe=$1
[[ ${MB} ]] && msize_MB=${MB}

if [[ ${CROSS_COMPILE} ]]; then
	case $(uname -m) in
	x86_64)
		pfx=qemu-aarch64-static
		;;
	aarch64)
		pfx=qemu-x86_64-static
		;;
	esac
fi

echo "$(./${exe} --uname)"
echo "${exe} $(./${exe} --version)"

# To avoid some memory boundary issues, it is not a power of 2, so choose "31".
for b in $(seq 16 31 8192)
do
	${pfx} ./${exe} --block-size ${b} --msize $((${MiB}*${msize_MB})) \
		${firstline:+--verbose}
	firstline=
done
