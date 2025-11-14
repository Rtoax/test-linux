__USE_TRACE_HELPERS__ := y

target-y := execsnoop
target-bpf-y := bpf_program.bpf.o
target-prep-y := vmlinux.h

LDFLAGS := -lelf -lbpf

include main.mk

execsnoop: loader.o bpf_load.o ${TRACE_HELPERS}
