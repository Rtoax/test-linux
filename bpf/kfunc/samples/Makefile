# SPDX-License-Identifier: GPL-3.0
target-prep-y := vmlinux.h

kfuncs := bpf_task_from_pid
helpers := bpf_strncmp

target-bpf-y := $(patsubst %,%.bpf.o,${kfuncs})
target-bpf-y += $(patsubst %,%.bpf.o,${helpers})

target-post-y := $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))

include main.mk
