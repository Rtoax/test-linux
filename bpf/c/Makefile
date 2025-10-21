# SPDX-License-Identifier: GPL-3.0
target-y := kprobe

target-bpf-y := foo.bpf.o

target-post-y := $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))
target-post-y += foo.c.s foo.o

CFLAGS += -DBCC=1
LDFLAGS := -lbpf -lbcc

CFLAGS_BPF_foo := -DBPF=1 -O0
CFLAGS_foo := -fomit-frame-pointer

include ../../template/main.mk

bpf_helpers.o: bpf_helpers.h
kprobe: kprobe.o bpf_helpers.o
