target-y += server
target-y += client

prog-y := gen-key.sh

CFLAGS += -I../macro/
LDFLAGS +=$(shell pkg-config --libs --cflags openssl)
