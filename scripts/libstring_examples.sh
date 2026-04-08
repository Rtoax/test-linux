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
   [[ $(size2bytes 123) -ne 123 ]] || \
   [[ $(size2bytes 12300111) -ne 12300111 ]]; then
	echo >&2 "ERROR: size2bytes() failed"
	exit 1
fi

# Test sizeceilfmt()
if [[ $(sizeceilfmt 0) != 0B ]] || \
   [[ $(sizeceilfmt 1) != 1B ]] || \
   [[ $(sizeceilfmt 1023) != 1023B ]] || \
   [[ $(sizeceilfmt 1024) != 1K ]] || \
   [[ $(sizeceilfmt 1025) != 2K ]] || \
   [[ $(sizeceilfmt 4096) != 4K ]] || \
   [[ $(sizeceilfmt $((${KiB} * 2 + 1))) != 3K ]] || \
   [[ $(sizeceilfmt $((${KiB} * 2 + ${KiB}))) != 3K ]] || \
   [[ $(sizeceilfmt $((${MiB} * 3 + 1))) != 4M ]] || \
   [[ $(sizeceilfmt $((${MiB} * 3 + ${MiB}))) != 4M ]] || \
   [[ $(sizeceilfmt $((${GiB} * 4 + 1))) != 5G ]] || \
   [[ $(sizeceilfmt $((${GiB} * 4 + ${GiB}))) != 5G ]] || \
   [[ $(sizeceilfmt ${GiB}) != 1G ]]; then
	echo >&2 "ERROR: sizeceilfmt() failed"
	exit 1
fi
