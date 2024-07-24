#!/bin/bash
version() {
	gcc -march=native -Q --help=target | grep -e '^  -march=' | awk '{print $2}'
}

macros() {
	gcc -march=native -dM -E - < /dev/null
}

version
if [[ $(uname -m) == x86_64 ]]; then
	macros | grep -e SSE -e AVX -e SVE -e NEON
# TODO: More architectures
fi
