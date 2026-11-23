include arch.mk
include os.mk
include musl-libc.mk

target-y += arch
target-y += os
target-${USE_MUSL_LIBC} += musl-libc

CFLAGS += ${cflags-arch}
CFLAGS += ${OS_CFLAGS}
CFLAGS += ${musl-libc-cflags}

prog-y += ${target-y}
prog-y += prep.sh
