# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-prep-y := vmlinux.h

kfuncs := task_from_pid
kfuncs += cgroup_from_id

helpers := trace_printk
helpers += strncmp
helpers += cgrp_storage_get
helpers += get_func_ip
helpers += loop

target-bpf-y := $(patsubst %,${OUTPUT}%.bpf.o,${kfuncs})
target-bpf-y += $(patsubst %,${OUTPUT}%.bpf.o,${helpers})

target-post-y := $(patsubst ${OUTPUT}%.bpf.o,${OUTPUT}%.bpf.disasm,$(target-bpf-y))

include main.mk
