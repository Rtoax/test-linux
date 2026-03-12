target-y += server
target-y += server-fork-pipe
target-y += server-pthread
target-y += client
target-y += client-pthread

server-objs := tcp_helpers.o
client-objs := tcp_helpers.o

LDFLAGS := -pthread
