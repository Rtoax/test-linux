# SPDX-License-Identifier: GPL-3.0
IF := lo
$(warning "Specify IF=[Interface] like IF=lo")

TARGET :=
TARGET += hello

BPF_OBJ = ${TARGET:=.bpf.o}

CLANG_CFLAGS := -target bpf -O2
CLANG_CFLAGS += -D__BPF_TRACING__
CLANG_CFLAGS += -I/usr/include/$(shell uname -m)-linux-gnu


.PHONY: build
build: $(BPF_OBJ)
	@echo >&2 ""
	@echo >&2 " make"
	@echo >&2 " make   install [IF=enp10s0]"
	@echo >&2 " make uninstall [IF=enp10s0]"
	@echo >&2 ""

$(BPF_OBJ): %.o: %.c vmlinux.h
	clang ${CLANG_CFLAGS} -o $@ -c $<

include ../../../bpftool/vmlinux.h.mk

install: $(BPF_OBJ)
	sudo bpftool prog load $(BPF_OBJ) /sys/fs/bpf/$(TARGET)
	sudo bpftool net attach xdp pinned /sys/fs/bpf/$(TARGET) dev ${IF}
	sudo bpftool net show

uninstall:
	sudo bpftool net detach xdp dev ${IF}
	sudo rm -f /sys/fs/bpf/$(TARGET)

clean:
	sudo rm -rf $(BPF_OBJ) vmlinux.h
