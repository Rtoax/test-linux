#!/bin/bash
set -e

. libstring.sh

# Test size2bytes()
if [[ $(size2bytes 8GiB) -ne $((8 * 1024 * 1024 * 1024)) ]] || \
   [[ $(size2bytes 1GB) -ne $((1 * 1024 * 1024 * 1024)) ]] || \
   [[ $(size2bytes 8G) -ne $((8 * 1024 * 1024 * 1024)) ]] || \
   [[ $(size2bytes 9MiB) -ne $((9 * 1024 * 1024)) ]] || \
   [[ $(size2bytes 9MB) -ne $((9 * 1024 * 1024)) ]] || \
   [[ $(size2bytes 8KiB) -ne $((8 * 1024)) ]] || \
   [[ $(size2bytes 8KB) -ne $((8 * 1024)) ]] || \
   [[ $(size2bytes 8K) -ne $((8 * 1024)) ]] || \
   [[ $(size2bytes 123) -ne 123 ]]; then
	echo >&2 "ERROR: size2bytes() failed"
	exit 1
fi
