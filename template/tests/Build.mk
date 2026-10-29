include os.mk

target-y += os

CFLAGS += ${OS_CFLAGS}

prog-y += ${target-y}
