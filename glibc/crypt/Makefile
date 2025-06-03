TARGETS := crypt
TARGETS += encrypt

CFLAGS := -Werror -Wall
CFLAGS += -lcrypt
CFLAGS += -D_XOPEN_SOURCE -D_GNU_SOURCE
CFLAGS += -Wno-error=implicit-function-declaration

LDFLAGS := -lcrypt
CFLAGS_crypt := -lcrypt

include ../../template/main.mk

crypt: crypt.o
encrypt: encrypt.o
