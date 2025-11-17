# SPDX-License-Identifier: GPL-3.0
target-prep-y := vmlinux.h

kfuncs := task_from_pid
kfuncs += cgroup_from_id
helpers := trace_printk
helpers += strncmp
helpers += cgrp_storage_get

target-bpf-y := $(patsubst %,%.bpf.o,${kfuncs})
target-bpf-y += $(patsubst %,%.bpf.o,${helpers})

target-post-y := $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))

include main.mk
