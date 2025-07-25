targets :=
targets += server
targets += server-fork-pipe
targets += server-pthread
targets += client
targets += client-pthread

include ../../../../template/main.mk

server: server.o tcp_helpers.o
server-pthread: server-pthread.o
server-fork-pipe: server-fork-pipe.o
client: client.o tcp_helpers.o
client-pthread: client-pthread.o
