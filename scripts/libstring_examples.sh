#!/bin/bash
set -e

. liblog.sh
. libstring.sh

# Test size2bytes()
if [[ $(size2bytes 8GiB) -ne $((8 * ${GiB})) ]] || \
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
	error "test size2bytes() failed"
fi

if [[ $(sizechkalign 1 0) != "" ]] ||
   [[ $(sizechkalign 1 1) != y ]] ||
   [[ $(sizechkalign 1024 1024) != y ]] ||
   [[ $(sizechkalign 1024 1021) != n ]] ||
   [[ $(sizechkalign 1K 1024) != y ]] ||
   [[ $(sizechkalign 1K 1) != y ]] ||
   [[ $(sizechkalign 1MiB 1KiB) != y ]] ||
   [[ $(sizechkalign 6MiB 3M) != y ]] ||
   [[ $(sizechkalign 6MiB 3) != y ]] ||
   [[ $(sizechkalign 1GiB 1K) != y ]]; then
	error "test sizechkalign() failed"
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
	error "test sizeceilfmt() failed"
fi

if [[ $(sizesum 0 1 2 3) != 6B ]] ||
   [[ $(sizesum 1K 2B) != 1026B ]] ||
   [[ $(sizesum 1GiB 2MB 3K 4B) != $((${GiB} + 2 * MiB + 3 * KiB + 4))B ]]; then
	error "test sizesum() failed"
fi
