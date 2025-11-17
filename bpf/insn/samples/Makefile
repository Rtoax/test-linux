# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-liba-y := libbpf_insn_samples.a
target-libso-y := libbpf_insn_samples.so

helplers := trace_printk
helplers += strncmp

static-objs := $(patsubst %,${OUTPUT}%.a.o,${helplers})
dynamic-objs := $(patsubst %,${OUTPUT}%.so.o,${helplers})

include main.mk

libbpf_insn_samples.a: ${static-objs}
libbpf_insn_samples.so: ${dynamic-objs}
