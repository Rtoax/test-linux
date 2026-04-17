# SPDX-License-Identifier: GPL-3.0
include glibc.mk

target-y += ansi_ascii
target-y += ctermid
target-y += asprintf vasprintf
target-y += snprintf sprintf
target-y += vfprintf
target-y += vsprintf
target-y += printf vprintf
target-y += puts
target-y += __freadable
target-y += open_memstream
target-y += remove
target-y += popen
target-y += fwrite
target-y += getchar
target-y += getline getdelim
target-y += scanf sscanf
target-y += perror
target-y += tmpfile tmpnam tempnam
target-y += setbuf setvbuf
target-y += fgets
target-y += fopen
target-y += fread
target-y += fscanf
target-y += fopencookie

CFLAGS_printf := -DLIBC_PRINTF_SYMADDR=$(call glibc_sym_addr,printf)
CFLAGS_getdelim := -DTEST_getdelim=1
CFLAGS_sprintf := -Wno-error=format-overflow
CFLAGS_snprintf := -Wno-error=format-truncation

target-prog-y := os-release.sh
