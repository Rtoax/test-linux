targets := unix-server
targets += unix-client
targets += unix-client-memfd_create
targets += socketpair

include ../../../template/main.mk

unix-server: unix-server.o common.o
unix-client: unix-client.o common.o
unix-client-memfd_create: unix-client-memfd_create.o common.o
socketpair: socketpair.o common.o
