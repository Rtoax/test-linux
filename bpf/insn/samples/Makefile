# SPDX-License-Identifier: GPL-3.0
__USE_BTF_HELPERS__ = y

OUTPUT := .output/

include kernel.mk

target-liba-y := libbpf_insn_samples.a
target-libso-y := libbpf_insn_samples.so

helpers := trace_printk
helpers += get_current_cgroup_id
# linux v5.16-rc4-1160-gc5fb19937455
# commit c5fb19937455 ("bpf: Add bpf_strncmp helper")
ifeq ($(call kver_ge,5,16,0),y)
  helpers += strncmp
endif
helpers += cgroup_acquire cgroup_from_id
helpers += task_from_pid
helpers += task_acquire
# linux v6.0-11954-gc4bcfb38a95e
# commit c4bcfb38a95e ("bpf: Implement cgroup storage available to non-cgroup-attached bpf progs")
ifeq ($(call kver_ge,6,0,0),y)
  helpers += cgrp_storage_get
endif
helpers += get_func_ip
# linux v5.15-12938-ge6f2dd0f8067
# commit e6f2dd0f8067 ("bpf: Add bpf_loop helper")
ifeq ($(call kver_ge,5,16,0),y)
  helpers += loop
endif
helpers += arena_alloc_pages arena_reserve_pages
helpers += strnstr

$(info helpers = ${helpers})

static-objs := $(patsubst %,${OUTPUT}%.a.o,${helpers})
dynamic-objs := $(patsubst %,${OUTPUT}%.so.o,${helpers})

include main.mk

libbpf_insn_samples.a: ${static-objs} ${OUTPUT}bpf_insn_samples.a.o
libbpf_insn_samples.so: ${dynamic-objs} ${OUTPUT}bpf_insn_samples.so.o
