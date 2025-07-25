targets :=
targets += sendfile
targets += sendfile-tcp-server
targets += sendfile-socket

CFLAGS :=
CFLAGS += -pthread

include ../../../template/main.mk

sendfile: sendfile.o
sendfile-tcp-server: sendfile-tcp-server.o
sendfile-socket: sendfile-socket.o
