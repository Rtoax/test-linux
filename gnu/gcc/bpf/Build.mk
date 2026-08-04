include bpf/gcc.mk

target-bpf-y += hello.bpf.o
target-bpf-${HAVE_BPF_GCC} += hello.bpf.gcc.o
