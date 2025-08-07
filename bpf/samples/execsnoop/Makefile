targets := execsnoop
targets-bpf := bpf_program.bpf.o
targets-prep := vmlinux.h

LDFLAGS := -lelf -lbpf

include ../../../template/main.mk

execsnoop: trace_helpers.o bpf_load.o loader.o
