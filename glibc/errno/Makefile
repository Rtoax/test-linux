include ../glibc.mk

targets := nr_errno
targets += __errno_location
targets += EDOM
targets += ENOENT
targets += EAFNOSUPPORT

CC := gcc

CFLAGS := -pthread
CFLAGS += -DLIBC___ERRNO_LOCATION_SYMADDR=${LIBC___ERRNO_LOCATION_SYMADDR}

targets-prep := nr_errno.h
targets-clean := clean-more

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
