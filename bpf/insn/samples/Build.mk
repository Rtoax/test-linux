# SPDX-License-Identifier: GPL-3.0
__USE_BTF_HELPERS__ = y

OUTPUT := .output/

include kernel.mk
include bpf/helper.mk

target-liba-y := libbpf_insn_samples.a
target-libso-y := libbpf_insn_samples.so

helpers-y := trace_printk
helpers-y += get_current_cgroup_id
helpers-y += get_current_task_btf
helpers-$(SUPPORT_BPF_STRNCMP) += strncmp
helpers-y += cgroup_acquire cgroup_from_id
helpers-y += task_from_pid
helpers-y += task_acquire
helpers-$(SUPPORT_BPF_CGRP_STORAGE_GET) += cgrp_storage_get
helpers-y += get_func_ip
helpers-$(SUPPORT_BPF_LOOP) += loop
helpers-y += arena_alloc_pages arena_reserve_pages
helpers-y += strnstr
helpers-y += iter_task_vma_new

$(info helpers-y = ${helpers-y})

static-objs := $(patsubst %,${OUTPUT}%.a.o,${helpers-y})
dynamic-objs := $(patsubst %,${OUTPUT}%.so.o,${helpers-y})

libbpf_insn_samples.a-objs := ${static-objs} ${OUTPUT}bpf_insn_samples.a.o
libbpf_insn_samples.so-objs := ${dynamic-objs} ${OUTPUT}bpf_insn_samples.so.o
