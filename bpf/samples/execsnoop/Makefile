target-y := execsnoop
target-bpf-y := bpf_program.bpf.o
target-prep-y := vmlinux.h

LDFLAGS := -lelf -lbpf

include ../../../template/main.mk

execsnoop: trace_helpers.o bpf_load.o loader.o
