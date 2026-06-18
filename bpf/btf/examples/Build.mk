# ref: https://www.kernel.org/doc/html/latest/bpf/btf.html
# 6. BTF Generation

target-bpf-y := ${OUTPUT}t1.bpf.o
target-bpf-y += ${OUTPUT}t2.bpf.o

post-y := ${OUTPUT}t1.bpf.btf
post-y += ${OUTPUT}t2.bpf.s
