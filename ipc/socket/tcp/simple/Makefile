TARGETS :=
TARGETS += server
TARGETS += server-fork-pipe
TARGETS += server-pthread
TARGETS += client
TARGETS += client-pthread

include ../../../../template/main.mk

server: server.o tcp_helpers.o
server-pthread: server-pthread.o
server-fork-pipe: server-fork-pipe.o
client: client.o tcp_helpers.o
client-pthread: client-pthread.o
