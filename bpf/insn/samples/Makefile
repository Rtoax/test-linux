# SPDX-License-Identifier: GPL-3.0
__USE_BTF_HELPERS__ = y

OUTPUT := .output/

target-liba-y := libbpf_insn_samples.a
target-libso-y := libbpf_insn_samples.so

helpers := trace_printk
helpers += strncmp
helpers += cgroup_from_id
helpers += task_from_pid
helpers += cgrp_storage_get
helpers += get_func_ip

static-objs := $(patsubst %,${OUTPUT}%.a.o,${helpers})
dynamic-objs := $(patsubst %,${OUTPUT}%.so.o,${helpers})

include main.mk

libbpf_insn_samples.a: ${static-objs}
libbpf_insn_samples.so: ${dynamic-objs}
