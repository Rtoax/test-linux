# SPDX-License-Identifier: GPL-3.0
include ../glibc.mk

targets :=
targets += ansi_ascii
targets += ctermid
targets += asprintf vasprintf
targets += snprintf sprintf
targets += vfprintf
targets += vsprintf
targets += printf vprintf
targets += puts
targets += __freadable
targets += open_memstream
targets += remove
targets += popen
targets += fwrite
targets += getchar
targets += getline getdelim
targets += scanf sscanf
targets += perror
targets += tmpfile tmpnam tempnam
targets += setbuf setvbuf
targets += fgets
targets += fopen
targets += fread
targets += fopencookie

ifneq ($(LIBC_PRINTF_SYMADDR),)
  CFLAGS += -DLIBC_PRINTF_SYMADDR=${LIBC_PRINTF_SYMADDR}
endif

CFLAGS_getdelim := -DTEST_getdelim=1
CFLAGS_sprintf := -Wno-error=format-overflow
CFLAGS_snprintf := -Wno-error=format-truncation

targets-post := os-release

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
