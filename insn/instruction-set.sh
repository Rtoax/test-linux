#!/bin/bash
set -e

readonly GCC=gcc

[[ -z ${CC} ]] && CC=${GCC}

version() {
	${GCC} -march=native -Q --help=target | grep -e '^  -march=' | awk '{print $2}'
}

macros() {
	# or $ echo | gcc -march=native -dM -E -
	${CC} -march=native -dM -E - < /dev/null
}

version
if [[ $(uname -m) == x86_64 ]]; then
	macros | grep -e MMX -e SSE -e AVX
elif [[ $(uname -m) == aarch64 ]]; then
	macros | grep -e SVE -e NEON
# TODO: More architectures
fi
