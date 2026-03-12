# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include bpf/kfunc.mk

target-prep-y := vmlinux.h

kfuncs-y := task_from_pid
kfuncs-y += cgroup_from_id
kfuncs-y += cgroup_acquire
kfuncs-$(SUPPORT_BPF_ITER_TASK_VMA_NEW) += iter_task_vma_new

helpers-y := trace_printk
helpers-y += strncmp
helpers-y += cgrp_storage_get
helpers-y += get_func_ip
helpers-y += loop
helpers-y += get_current_task_btf

target-bpf-y := $(patsubst %,${OUTPUT}%.bpf.o,${kfuncs-y})
target-bpf-y += $(patsubst %,${OUTPUT}%.bpf.o,${helpers-y})

target-post-y := $(patsubst ${OUTPUT}%.bpf.o,${OUTPUT}%.bpf.disasm,$(target-bpf-y))
