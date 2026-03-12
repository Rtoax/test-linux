include glibc.mk

target-y := nr_errno
target-y += __errno_location
target-y += EDOM
target-y += ENOENT
target-y += EAFNOSUPPORT

LDFLAGS := -pthread
CFLAGS___errno_location := -DLIBC___ERRNO_LOCATION_SYMADDR=$(call libc_sym_addr,__errno_location)

target-clean-y := clean-more

nr_errno.o: nr_errno.h

nr_errno.h: errno.sh
	$(shell bash errno.sh)

clean-more:
	${Q}rm -f nr_errno.h
