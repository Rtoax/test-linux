target-y := unix-server
target-y += unix-client
target-y += unix-client-memfd_create
target-y += socketpair

unix-server-objs := iovec_helpers.o
unix-client-objs := iovec_helpers.o
unix-client-memfd_create-objs := iovec_helpers.o
socketpair-objs := iovec_helpers.o

CFLAGS_unix-client-memfd_create := -DMEMFD=1
