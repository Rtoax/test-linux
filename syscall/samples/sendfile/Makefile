TARGETS :=
TARGETS += sendfile
TARGETS += sendfile-tcp-server
TARGETS += sendfile-socket

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread

include ../../../template/main.mk

sendfile: sendfile.o
sendfile-tcp-server: sendfile-tcp-server.o
sendfile-socket: sendfile-socket.o
