#!/bin/bash
set -e

readonly GCC=gcc
readonly CPUID=$(which cpuid 2>/dev/null)

declare -a CFLAGS

[[ -z ${CC} ]] && CC=${GCC}

case $(uname -m) in
ppc64le)
	CFLAGS+=( -mcpu=native -m64 )
	;;
*)
	CFLAGS+=( -march=native )
	;;
esac

version() {
	${GCC} ${CFLAGS[@]} -Q --help=target | \
		grep -e '^  -march=' -e '^  -mcpu=' | \
		awk '{print $2}'
}

macros() {
	# or $ echo | gcc -march=native -dM -E -
	${CC} ${CFLAGS[@]} -dM -E - < /dev/null
}

version
if [[ $(uname -m) == x86_64 ]]; then
	macros | grep -e MMX -e SSE -e AVX
elif [[ $(uname -m) == aarch64 ]]; then
	macros | grep -e SVE -e NEON
elif [[ $(uname -m) == ppc64le ]]; then
	macros | head -10
# TODO: More architectures
fi
