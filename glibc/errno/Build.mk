include glibc.mk

target-y += errors
target-y += nr_errno
target-y += __errno_location
target-y += EDOM
target-y += ENOENT
target-y += EAFNOSUPPORT

target-clean-y := clean-more

LDFLAGS := -pthread
CFLAGS___errno_location := -DLIBC___ERRNO_LOCATION_SYMADDR=$(call libc_sym_addr,__errno_location)
