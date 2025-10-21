target-y := unix-server
target-y += unix-client
target-y += unix-client-memfd_create
target-y += socketpair

CFLAGS_unix-client-memfd_create := -DMEMFD=1

include ../../../template/main.mk

iovec_helpers.o: iovec_helpers.h

unix-server: unix-server.o iovec_helpers.o
unix-client: unix-client.o iovec_helpers.o
unix-client-memfd_create: unix-client-memfd_create.o iovec_helpers.o
socketpair: socketpair.o iovec_helpers.o
