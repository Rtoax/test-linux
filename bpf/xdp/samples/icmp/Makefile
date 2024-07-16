SHELL = bash

TARGET = hello

ARCH = $(shell uname -m | sed 's/x86_64/x86/' | sed 's/aarch64/arm64/')

BPF_OBJ = ${TARGET:=.bpf.o}

CLANG_CFLAGS := -target bpf -O2
CLANG_CFLAGS += -D__BPF_TRACING__
CLANG_CFLAGS += -I/usr/include/$(shell uname -m)-linux-gnu

all: $(TARGET) $(BPF_OBJ)
.PHONY: all
.PHONY: $(TARGET)

$(TARGET): $(BPF_OBJ)
	sudo bpftool net detach xdp dev lo
	sudo rm -f /sys/fs/bpf/$(TARGET)
	sudo bpftool prog load $(BPF_OBJ) /sys/fs/bpf/$(TARGET)
	sudo bpftool net attach xdp pinned /sys/fs/bpf/$(TARGET) dev lo

$(BPF_OBJ): %.o: %.c vmlinux.h
	clang ${CLANG_CFLAGS} -o $@ -c $<

vmlinux.h:
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

clean:
	sudo bpftool net detach xdp dev lo
	sudo rm -f /sys/fs/bpf/$(TARGET) $(BPF_OBJ) vmlinux.h
