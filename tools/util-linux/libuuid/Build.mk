include util-linux.mk

target-y += base

prog-y += ${target-y}

LDFLAGS += -luuid
