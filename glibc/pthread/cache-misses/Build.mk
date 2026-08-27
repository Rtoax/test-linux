include cpu.mk

target-y := struct

prog-y += ${target-y}

CFLAGS := ${cpu-cflags}
LDFLAGS := -pthread
