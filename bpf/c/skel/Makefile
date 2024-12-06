# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


ARCH ?= $(shell uname -m | sed 's/x86_64/x86/' \
			 | sed 's/arm.*/arm/' \
			 | sed 's/aarch64/arm64/' \
			 | sed 's/ppc64le/powerpc/' \
			 | sed 's/mips.*/mips/' \
			 | sed 's/riscv64/riscv/' \
			 | sed 's/loongarch64/loongarch/')

CC := gcc
CLANG := clang
BPFTOOL := bpftool

TARGETS_BPF :=
TARGETS_BPF += tc.bpf.o

TARGETS_EXE :=
TARGETS_EXE += tc

CFLAGS_BPF := -I.
CFLAGS_BPF += -O2 -Wall
CFLAGS_BPF += -target bpf
CFLAGS_BPF += -D__TARGET_ARCH_$(ARCH)

CFLAGS_EXE := -lbpf
LDFLAGS_EXE := -lbpf


.PHONY: build
build: vmlinux.h ${TARGETS_BPF} ${TARGETS_EXE}

$(patsubst %,%.o,$(TARGETS_EXE)): %.o: %.skel.h

%.bpf.o: %.bpf.c
	@echo -e "  BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF}

%.skel.h: %.bpf.o
	@echo -e "  SKEL  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(BPFTOOL) gen skeleton $< > $@

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS_EXE) $(CFLAGS_EXE_$(*))

$(TARGETS_EXE): %: %.o
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS_EXE) $(LDFLAGS_EXE_$(*))

vmlinux.h:
	@echo -e "  BPFTOOL  \033[1m$(@)\033[m"
	${Q}${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

clean:
	@echo -e "  RM  \033[1;32m$(TARGETS_BPF) ${TARGETS_EXE}\033[m"
	${Q}rm -f ${TARGETS_BPF} ${TARGETS_EXE} *.o *.skel.h vmlinux.h
