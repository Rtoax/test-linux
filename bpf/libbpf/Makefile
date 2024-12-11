# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

CONFIG_KERNEL ?= /boot/config-$(shell uname -r)

ifeq ($(wildcard $(CONFIG_KERNEL)),)
  $(error "ERROR: Not found ${CONFIG_KERNEL}")
endif

include $(CONFIG_KERNEL)

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

kernel-config-y :=
kernel-config-$(CONFIG_KPROBES) += kprobe
kernel-config-$(CONFIG_TRACEPOINTS) += tracepoint raw_tracepoint

$(info kernel-config-y : $(kernel-config-y))

ifneq ($(kernel-config-),)
  $(warning Not support ${kernel-config-})
endif

TARGETS :=
TARGETS += config-map
TARGETS += socket_filter
TARGETS += tc
TARGETS += xdp
TARGETS += $(kernel-config-y)


TARGETS_BPF := ${TARGETS:=.bpf.o}
TARGETS_SKEL := ${TARGETS:=.skel.h}

CFLAGS_BPF := -I.
CFLAGS_BPF += -O2 -Wall -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += -D__TARGET_ARCH_$(ARCH)

CFLAGS := -lbpf
LDFLAGS := -lbpf

CFLAGS_socket_filter := -DSTRICT_SEC_NAME=1
CFLAGS_BPF_socket_filter := -DSTRICT_SEC_NAME=1
CFLAGS_tracepoint := -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_tracepoint := -DSEC_DEF_TRACEPOINT=1
CFLAGS_raw_tracepoint := -DSEC_DEF_RAW_TRACEPOINT=1
CFLAGS_BPF_raw_tracepoint := -DSEC_DEF_RAW_TRACEPOINT=1
CFLAGS_xdp := -DSTRICT_SEC_NAME=1
CFLAGS_BPF_xdp := -DSTRICT_SEC_NAME=1


.PHONY: build
build: vmlinux.h ${TARGETS_BPF} ${TARGETS_SKEL} ${TARGETS}

$(patsubst %,%.o,$(TARGETS)): %.o: %.skel.h

%.bpf.o: %.bpf.c
	@echo -e "  BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

%.skel.h: %.bpf.o
	@echo -e "  SKEL  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(BPFTOOL) gen skeleton $< > $@

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %: %.o
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

vmlinux.h:
	@echo -e "  BPFTOOL  \033[1m$(@)\033[m"
	${Q}${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

clean:
	@echo -e "  RM  \033[1;32m$(TARGETS_BPF) ${TARGETS}\033[m"
	${Q}rm -f ${TARGETS_BPF} ${TARGETS} *.o *.skel.h vmlinux.h
