TARGETS :=
TARGETS += server client
TARGETS += stress-send stress-recv

TARGETS_CPP := client_cc

include ../../../../template/main.mk

server: server.o
client: client.o
client_cc: client_cc.opp
stress-send: stress-send.o
stress-recv: stress-recv.o
