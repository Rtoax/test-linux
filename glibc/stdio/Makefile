# SPDX-License-Identifier: GPL-3.0
include ../glibc.mk

target-y :=
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
target-y += fopencookie

ifneq ($(LIBC_PRINTF_SYMADDR),)
  CFLAGS += -DLIBC_PRINTF_SYMADDR=${LIBC_PRINTF_SYMADDR}
endif

CFLAGS_getdelim := -DTEST_getdelim=1
CFLAGS_sprintf := -Wno-error=format-overflow
CFLAGS_snprintf := -Wno-error=format-truncation

target-post-y := os-release

include ../../template/main.mk

os-release:
	@cp /etc/os-release os-release

ansi_ascii: ansi_ascii.o
ctermid: ctermid.o
asprintf: asprintf.o
vasprintf: vasprintf.o
vfprintf: vfprintf.o
vsprintf: vsprintf.o
printf: printf.o
vprintf: vprintf.o
__freadable: __freadable.o
open_memstream: open_memstream.o
remove: remove.o
popen: popen.o
fwrite: fwrite.o
getchar: getchar.o
getline: getline.o
getdelim: getdelim.o
puts: puts.o
scanf: scanf.o
sscanf: sscanf.o
perror: perror.o
tmpfile: tmpfile.o
tmpnam: tmpnam.o
tempnam: tempnam.o
sprintf: sprintf.o
snprintf: snprintf.o
setbuf: setbuf.o
setvbuf: setvbuf.o
fgets: fgets.o
fopen: fopen.o
fread: fread.o
fopencookie: fopencookie.o
