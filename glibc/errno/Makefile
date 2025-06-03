include ../glibc.mk

TARGETS := nr_errno
TARGETS += __errno_location
TARGETS += EDOM
TARGETS += ENOENT
TARGETS += EAFNOSUPPORT

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread

CFLAGS += -DLIBC___ERRNO_LOCATION_SYMADDR=${LIBC___ERRNO_LOCATION_SYMADDR}

TARGETS_PRE := nr_errno.h
TARGETS_CLEAN := clean-more

include ../../elf/pie.mk
include ../../template/main.mk

nr_errno.h: errno.sh
	$(shell bash errno.sh)

nr_errno: nr_errno.o
nr_errno.o: nr_errno.h
__errno_location: __errno_location.o
EDOM: EDOM.o
ENOENT: ENOENT.o
EAFNOSUPPORT: EAFNOSUPPORT.o

clean-more:
	${Q}rm -f nr_errno.h
