subdir-y += string

bpftrace-y += $(shell ls *.bt)

bpf-c += $(shell ls *.bpf.c)
target-bpf-y += $(patsubst %.bpf.c,%.bpf.o,${bpf-c})
