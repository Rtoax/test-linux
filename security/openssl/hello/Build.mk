target-y += server
target-y += client

target-prog-y := gen-key.sh

CFLAGS += -I../macro/
LDFLAGS +=$(shell pkg-config --libs --cflags openssl)
