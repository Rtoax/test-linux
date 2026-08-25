include bpf/bpftrace.mk

bpftrace-y += strcat.bt

target-bpf-y += str_concat.bpf.o
