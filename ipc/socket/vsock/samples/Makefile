targets :=
targets += server
targets += client

CFLAGS := -pthread

include ../../../../template/main.mk

../vsock_helpers.o: ../vsock_helpers.h
server.o: config.h
server: server.o ../vsock_helpers.o
client.o: config.h
client: client.o ../vsock_helpers.o
