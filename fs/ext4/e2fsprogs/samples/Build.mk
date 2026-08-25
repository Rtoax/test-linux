include fs/e2fsprogs.mk

target-y += metadata

CFLAGS += ${e2fsprogs-cflags}
LDFLAGS += ${e2fsprogs-ldflags}
