__USE_TRACE_HELPERS__ := y

target-y := execsnoop
target-bpf-y := bpf_program.bpf.o
target-prep-y := vmlinux.h

LDFLAGS := -lelf -lbpf

include ../../../template/main.mk

execsnoop: ${TRACE_HELPERS} bpf_load.o loader.o
