target-y := crypt
target-y += encrypt

prog-y += $(filter-out crypt, ${target-y})

CFLAGS += -D_XOPEN_SOURCE
CFLAGS += -Wno-error=implicit-function-declaration

LDFLAGS := -lcrypt
