#!/bin/bash
set -e

source /etc/profile
export -f make_tl

readonly MiB=1024*1024

make_tl

pfx=
exes=( memcpy-stress
	__memcpy_ssse3-stress
	__memcpy_generic-stress
	__memcpy_simd-stress
	__memcpy_a64fx-stress
	__memcpy_aarch64-stress
	__memcpy_aarch64_simd-stress
	__memcpy_aarch64_sve-stress )

msize_MB=1024*4

[[ $1 ]] && exes=( $1 )
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

for exe in ${exes}
do
	firstline=YES

	if [[ ! -e ${exe} ]]; then
		echo "WARNING: not support ${exe}"
		continue
	fi

	echo "$(./${exe} --uname)"
	echo "${exe} $(./${exe} --version)"

	# To avoid some memory boundary issues, it is not a power of 2, so choose "31".
	for b in $(seq 16 31 8192)
	do
		${pfx} ./${exe} --iosize ${b} --msize $((${MiB}*${msize_MB})) \
			${firstline:+--verbose}
		firstline=
	done
done
