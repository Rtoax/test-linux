#!/bin/bash
set -e

version() {
	# Or no need to -march parameter
	gcc -march=native -Q --help=target | grep -e '^  -march=' | awk '{print $2}'
}

macros() {
	gcc -march=native -dM -E - < /dev/null
}

version
if [[ $(uname -m) == x86_64 ]]; then
	macros | grep -e MMX -e SSE -e AVX
elif [[ $(uname -m) == aarch64 ]]; then
	macros | grep -e SVE -e NEON
# TODO: More architectures
fi
