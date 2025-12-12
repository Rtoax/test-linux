# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include glibc.mk

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
target-y += fscanf
target-y += fopencookie

ifneq ($(LIBC_PRINTF_SYMADDR),)
  CFLAGS += -DLIBC_PRINTF_SYMADDR=${LIBC_PRINTF_SYMADDR}
endif

CFLAGS_getdelim := -DTEST_getdelim=1
CFLAGS_sprintf := -Wno-error=format-overflow
CFLAGS_snprintf := -Wno-error=format-truncation

target-post-y := os-release

include main.mk

os-release:
	${Q}cp /etc/os-release os-release

ansi_ascii: ${OUTPUT}ansi_ascii.o
ctermid: ${OUTPUT}ctermid.o
asprintf: ${OUTPUT}asprintf.o
vasprintf: ${OUTPUT}vasprintf.o
vfprintf: ${OUTPUT}vfprintf.o
vsprintf: ${OUTPUT}vsprintf.o
printf: ${OUTPUT}printf.o
vprintf: ${OUTPUT}vprintf.o
__freadable: ${OUTPUT}__freadable.o
open_memstream: ${OUTPUT}open_memstream.o
remove: ${OUTPUT}remove.o
popen: ${OUTPUT}popen.o
fwrite: ${OUTPUT}fwrite.o
getchar: ${OUTPUT}getchar.o
getline: ${OUTPUT}getline.o
getdelim: ${OUTPUT}getdelim.o
puts: ${OUTPUT}puts.o
scanf: ${OUTPUT}scanf.o
sscanf: ${OUTPUT}sscanf.o
perror: ${OUTPUT}perror.o
tmpfile: ${OUTPUT}tmpfile.o
tmpnam: ${OUTPUT}tmpnam.o
tempnam: ${OUTPUT}tempnam.o
sprintf: ${OUTPUT}sprintf.o
snprintf: ${OUTPUT}snprintf.o
setbuf: ${OUTPUT}setbuf.o
setvbuf: ${OUTPUT}setvbuf.o
fgets: ${OUTPUT}fgets.o
fopen: ${OUTPUT}fopen.o
fread: ${OUTPUT}fread.o
fscanf: ${OUTPUT}fscanf.o
fopencookie: ${OUTPUT}fopencookie.o
