targets :=
targets += server client
targets += stress-send stress-recv

targets-cpp := client_cc

include ../../../../template/main.mk

server: server.o
client: client.o
client_cc: client_cc.cpp.o
stress-send: stress-send.o
stress-recv: stress-recv.o
