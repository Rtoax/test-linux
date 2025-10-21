target-y :=
target-y += server
target-y += server-fork-pipe
target-y += server-pthread
target-y += client
target-y += client-pthread

include ../../../../template/main.mk

server: server.o tcp_helpers.o
server-pthread: server-pthread.o
server-fork-pipe: server-fork-pipe.o
client: client.o tcp_helpers.o
client-pthread: client-pthread.o
