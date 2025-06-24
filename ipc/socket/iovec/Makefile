TARGETS := unix-server
TARGETS += unix-client
TARGETS += unix-client-memfd_create
TARGETS += socketpair

include ../../../template/main.mk

unix-server: unix-server.o common.o
unix-client: unix-client.o common.o
unix-client-memfd_create: unix-client-memfd_create.o common.o
socketpair: socketpair.o
