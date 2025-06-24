TARGETS := crypt
TARGETS += encrypt

CFLAGS :=
CFLAGS += -lcrypt
CFLAGS += -D_XOPEN_SOURCE
CFLAGS += -Wno-error=implicit-function-declaration

LDFLAGS := -lcrypt
CFLAGS_crypt := -lcrypt

include ../../template/main.mk

crypt: crypt.o
encrypt: encrypt.o
