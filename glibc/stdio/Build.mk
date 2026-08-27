# SPDX-License-Identifier: GPL-3.0
include glibc.mk

target-y += __freadable
target-y += ansi_ascii
target-y += asprintf
target-y += ctermid
target-y += fgets
target-y += fopen
target-y += fopencookie
target-y += fread
target-y += fscanf
target-y += ftell
target-y += fwrite
target-y += getchar
target-y += getdelim
target-y += getline
target-y += open_memstream
target-y += perror
target-y += popen
target-y += printf
target-y += puts
target-y += remove
target-y += scanf
target-y += setbuf
target-y += setvbuf
target-y += snprintf
target-y += sprintf
target-y += sscanf
target-y += stdin
target-y += tempnam
target-y += tmpfile
target-y += tmpnam
target-y += vasprintf
target-y += vfprintf
target-y += vprintf
target-y += vsprintf

prog-y := os-release.sh
prog-y += $(filter-out getchar getline getdelim scanf stdin, ${target-y})

CFLAGS_printf := -DLIBC_PRINTF_SYMADDR=$(call glibc_sym_addr,printf)
CFLAGS_getdelim := -DTEST_getdelim=1
CFLAGS_sprintf := -Wno-error=format-overflow
CFLAGS_snprintf := -Wno-error=format-truncation
