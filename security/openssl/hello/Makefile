TARGETS :=
TARGETS += server
TARGETS += client

TARGETS_SHELL := gen-key.sh

CFLAGS :=
CFLAGS += -I../macro/
LDFLAGS +=$(shell pkg-config --libs --cflags openssl)

include ../../../template/main.mk

server: server.o
client: client.o
