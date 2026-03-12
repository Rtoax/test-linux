# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-y := hello

target-bpf-y := $(patsubst %,${OUTPUT}%.bpf.o,${target-y})

CFLAGS += -I${OUTPUT}
LDFLAGS += -lbpf
