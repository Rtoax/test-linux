#!/bin/bash
version() {
	gcc -march=native -Q --help=target | grep -e '^  -march=' | awk '{print $2}'
}

macros() {
	gcc -march=native -dM -E - < /dev/null
}

version
macros | grep -e SSE -e AVX
