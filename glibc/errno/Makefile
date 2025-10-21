include ../glibc.mk

target-y := nr_errno
target-y += __errno_location
target-y += EDOM
target-y += ENOENT
target-y += EAFNOSUPPORT

CC := gcc

CFLAGS := -pthread
CFLAGS += -DLIBC___ERRNO_LOCATION_SYMADDR=${LIBC___ERRNO_LOCATION_SYMADDR}

target-prep-y := nr_errno.h
target-clean-y := clean-more

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
