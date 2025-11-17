# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-liba-y := libbpf_insn_samples.a
target-libso-y := libbpf_insn_samples.so

include main.mk

libbpf_insn_samples.a: ${OUTPUT}trace_printk.a.o
libbpf_insn_samples.so: ${OUTPUT}trace_printk.so.o
