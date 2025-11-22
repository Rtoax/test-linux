# SPDX-License-Identifier: GPL-3.0
__USE_BTF_HELPERS__ = y

OUTPUT := .output/

include kernel.mk
include bpf/helper.mk

target-liba-y := libbpf_insn_samples.a
target-libso-y := libbpf_insn_samples.so

helpers-y := trace_printk
helpers-y += get_current_cgroup_id
helpers-$(SUPPORT_BPF_STRNCMP) += strncmp
helpers-y += cgroup_acquire cgroup_from_id
helpers-y += task_from_pid
helpers-y += task_acquire
# linux v6.0-11954-gc4bcfb38a95e
# commit c4bcfb38a95e ("bpf: Implement cgroup storage available to non-cgroup-attached bpf progs")
ifeq ($(call kver_ge,6,0,0),y)
  helpers-y += cgrp_storage_get
endif
helpers-y += get_func_ip
# linux v5.15-12938-ge6f2dd0f8067
# commit e6f2dd0f8067 ("bpf: Add bpf_loop helper")
ifeq ($(call kver_ge,5,16,0),y)
  helpers-y += loop
endif
helpers-y += arena_alloc_pages arena_reserve_pages
helpers-y += strnstr
helpers-y += iter_task_vma_new

$(info helpers-y = ${helpers-y})

static-objs := $(patsubst %,${OUTPUT}%.a.o,${helpers-y})
dynamic-objs := $(patsubst %,${OUTPUT}%.so.o,${helpers-y})

include main.mk

libbpf_insn_samples.a: ${static-objs} ${OUTPUT}bpf_insn_samples.a.o
libbpf_insn_samples.so: ${dynamic-objs} ${OUTPUT}bpf_insn_samples.so.o
