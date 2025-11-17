# SPDX-License-Identifier: GPL-3.0
__USE_BPF_HELPERS__ = y
__USE_BTF_HELPERS__ = y
__USE_BPF_INSN_SAMPLES__ = y

include bpf/bcc.mk

target-y := kprobe

target-bpf-y := foo.bpf.o

target-post-y := $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))
target-post-y += foo.c.s foo.o

CFLAGS += $(bcc-cflags)
LDFLAGS += -lbpf $(bcc-ldflags)

CFLAGS_BPF_foo := -DBPF=1 -O0
CFLAGS_foo := -fomit-frame-pointer

include main.mk

kprobe: kprobe.o ${BPF_INSN_SAMPLES} ${BPF_HELPERS} ${BTF_HELPERS}
