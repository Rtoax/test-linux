target-y :=
target-y += server client
target-y += stress-send stress-recv

target-cpp-y := client_cc

include ../../../../template/main.mk

server: server.o
client: client.o
client_cc: client_cc.cpp.o
stress-send: stress-send.o
stress-recv: stress-recv.o
