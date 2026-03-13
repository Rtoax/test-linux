# SPDX-License-Identifier: GPL-3.0
include bpf/bcc.mk
include helpers.mk

target-y := bpfprobe

target-bpf-y := ${OUTPUT}foo.bpf.o

target-post-y := $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))
target-post-y += ${OUTPUT}foo.c.s ${OUTPUT}foo.o

bpfprobe-objs := ${BPF_INSN_SAMPLES} ${BPF_HELPERS} ${BTF_HELPERS}

CFLAGS += $(bcc-cflags)
LDFLAGS += -lbpf $(bcc-ldflags)

CFLAGS_BPF_foo := -DBPF=1 -O0
CFLAGS_foo := -fomit-frame-pointer
