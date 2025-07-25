targets :=
targets += server
targets += client

targets-shell := gen-key.sh

CFLAGS :=
CFLAGS += -I../macro/
LDFLAGS +=$(shell pkg-config --libs --cflags openssl)

include ../../../template/main.mk

server: server.o
client: client.o
