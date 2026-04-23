include helpers.mk

target-y := execsnoop
target-bpf-y := ${OUTPUT}bpf_program.bpf.o
target-prep-y := vmlinux.h

execsnoop-objs := loader.o bpf_load.o ${TRACE_HELPERS}

LDFLAGS := -lelf -lbpf
