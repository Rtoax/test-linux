# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-y := hello

target-bpf-y := $(patsubst %,${OUTPUT}%.bpf.o,${target-y})

CFLAGS += -I${OUTPUT}
LDFLAGS += -lbpf

include main.mk

${OUTPUT}hello.o: ${OUTPUT}hello.skel.h
