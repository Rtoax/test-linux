# SPDX-License-Identifier: GPL-3.0
include ../glibc.mk

TARGETS :=
TARGETS += ansi_ascii
TARGETS += ctermid
TARGETS += asprintf vasprintf
TARGETS += snprintf sprintf
TARGETS += vfprintf
TARGETS += vsprintf
TARGETS += printf vprintf
TARGETS += puts
TARGETS += __freadable
TARGETS += open_memstream
TARGETS += remove
TARGETS += popen
TARGETS += fwrite
TARGETS += getchar
TARGETS += getline getdelim
TARGETS += scanf sscanf
TARGETS += perror
TARGETS += tmpfile tmpnam tempnam
TARGETS += setbuf setvbuf
TARGETS += fgets
TARGETS += fopen
TARGETS += fread
TARGETS += fopencookie

CFLAGS :=

ifneq ($(LIBC_PRINTF_SYMADDR),)
  CFLAGS += -DLIBC_PRINTF_SYMADDR=${LIBC_PRINTF_SYMADDR}
endif

CFLAGS_getdelim := -DTEST_getdelim=1
CFLAGS_sprintf := -Wno-error=format-overflow

TARGETS_POST := os-release

include ../../elf/pie.mk
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
