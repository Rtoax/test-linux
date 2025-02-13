# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

include ../glibc.mk

TARGETS :=
TARGETS += ansi_ascii
TARGETS += ctermid
TARGETS += asprintf vasprintf
TARGETS += snprintf
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
TARGETS += getline
TARGETS += scanf sscanf
TARGETS += perror
TARGETS += tmpfile tmpnam tempnam
TARGETS += setbuf setvbuf
TARGETS += fgets
TARGETS += fopen
TARGETS += fopencookie

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

ifneq ($(LIBC_PRINTF_SYMADDR),)
  CFLAGS += -DLIBC_PRINTF_SYMADDR=${LIBC_PRINTF_SYMADDR}
endif

include ../../elf/pie.mk

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
endif

build: ${TARGETS}
	@cp /etc/os-release os-release
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
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
puts: puts.o
scanf: scanf.o
sscanf: sscanf.o
perror: perror.o
tmpfile: tmpfile.o
tmpnam: tmpnam.o
tempnam: tempnam.o
snprintf: snprintf.o
setbuf: setbuf.o
setvbuf: setvbuf.o
fgets: fgets.o
fopen: fopen.o
fopencookie: fopencookie.o

CFLAGS_asprintf := -D_GNU_SOURCE=1

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./getchar < getchar.c
	echo 1.2 | ./scanf
	./fopencookie 'hello world'

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.log *.out *.bin os-release
