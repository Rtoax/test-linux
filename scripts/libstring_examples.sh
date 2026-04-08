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
   [[ $(size2bytes 0) -ne 0 ]] || \
   [[ $(size2bytes 123) -ne 123 ]] || \
   [[ $(size2bytes 12300111) -ne 12300111 ]]; then
	echo >&2 "ERROR: test size2bytes() failed"
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
   [[ $(sizeceilfmt ${GiB}) != 1G ]] || \
   [[ $(sizeceilfmt 1K) != 1K ]] || \
   [[ $(sizeceilfmt 1KB) != 1K ]] || \
   [[ $(sizeceilfmt 1KiB) != 1K ]] || \
   [[ $(sizeceilfmt 1023KiB) != 1023K ]] || \
   [[ $(sizeceilfmt 1024KiB) != 1M ]] || \
   [[ $(sizeceilfmt 1025KiB) != 2M ]] || \
   [[ $(sizeceilfmt 1M) != 1M ]] || \
   [[ $(sizeceilfmt 1MB) != 1M ]] || \
   [[ $(sizeceilfmt 1MiB) != 1M ]] || \
   [[ $(sizeceilfmt 1023MiB) != 1023M ]] || \
   [[ $(sizeceilfmt 1024MiB) != 1G ]] || \
   [[ $(sizeceilfmt 1025MiB) != 2G ]] || \
   [[ $(sizeceilfmt 1G) != 1G ]] || \
   [[ $(sizeceilfmt 1GB) != 1G ]] || \
   [[ $(sizeceilfmt 1GiB) != 1G ]] || \
   [[ $(sizeceilfmt 1023GiB) != 1023G ]] || \
   [[ $(sizeceilfmt 1025GiB) != 1025G ]]; then
	echo >&2 "ERROR: test sizeceilfmt() failed"
	exit 1
fi
