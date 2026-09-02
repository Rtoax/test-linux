include bpf/bpftrace.mk

subdir-y += error

bpftrace-y += strcat.bt

target-bpf-y += str_concat.bpf.o
