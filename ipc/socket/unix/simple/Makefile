TARGETS :=
TARGETS += tcp-server tcp-client tcp-server-noclose
TARGETS += udp-server udp-client

CFLAGS_tcp-server-noclose := -DNO_CLOSE_CLIENT_FD=1

include ../../../../template/main.mk

tcp-server: tcp-server.o
tcp-server-noclose: tcp-server-noclose.o
tcp-client: tcp-client.o
udp-server: udp-server.o
udp-client: udp-client.o
