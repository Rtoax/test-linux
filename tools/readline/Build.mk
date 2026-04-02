include readline.mk

target-y += rlversion
target-y += rltest

LDFLAGS += ${readline-ldflags}
