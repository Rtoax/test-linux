target-y :=
target-y += sendfile
target-y += sendfile-tcp-server
target-y += sendfile-socket

CFLAGS :=
CFLAGS += -pthread

include ../../../template/main.mk

sendfile: sendfile.o
sendfile-tcp-server: sendfile-tcp-server.o
sendfile-socket: sendfile-socket.o
