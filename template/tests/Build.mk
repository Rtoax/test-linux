include arch.mk
include os.mk

target-y += arch
target-y += os

CFLAGS += ${cflags-arch}
CFLAGS += ${OS_CFLAGS}

prog-y += ${target-y}
prog-y += prep.sh
