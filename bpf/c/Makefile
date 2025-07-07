# SPDX-License-Identifier: GPL-3.0
TARGETS := kprobe

TARGETS_BPF := foo.bpf.o

TARGETS_POST := $(patsubst %.bpf.o,%.bpf.disasm,$(TARGETS_BPF))

CFLAGS += -DBCC=1
LDFLAGS := -lbpf -lbcc

include ../../template/main.mk

bpf_helpers.o: bpf_helpers.h
kprobe: kprobe.o bpf_helpers.o
