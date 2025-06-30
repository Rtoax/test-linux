TARGETS := execsnoop
TARGETS_BPF := bpf_program.bpf.o
TARGETS_PREP := vmlinux.h

LDFLAGS := -lelf -lbpf

include ../../../template/main.mk

execsnoop: trace_helpers.o bpf_load.o loader.o

include ../../bpftool/vmlinux.h.mk
