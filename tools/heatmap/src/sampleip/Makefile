
ARCH ?= $(shell uname -m | sed 's/x86_64/x86/' | sed 's/aarch64/arm64/')

CFLAGS := -O0 -Wall -g -ggdb

all:
	clang -nostdinc -I/usr/include -fno-stack-protector -g \
		-D__BPF_TRACING__ -Wno-unused-value -Wno-pointer-sign \
		-D__TARGET_ARCH_$(ARCH) -Wno-compare-distinct-pointer-types \
		-Wno-gnu-variable-sized-type-not-at-end \
		-Wno-address-of-packed-member -Wno-tautological-compare \
		-Wno-unknown-warning-option  \
		-fno-asynchronous-unwind-tables \
		-I. \
		-O2 -emit-llvm -Xclang -disable-llvm-passes -c sampleip_kern.c -o - | \
		opt -O2 -mtriple=bpf-pc-linux | llvm-dis | \
		llc -march=bpf  -filetype=obj -o sampleip_kern.o

	clang sampleip_user.c trace_helpers.c -lbpf -o sampleip

clean:
	rm -f *.o sampleip vmlinux.h

