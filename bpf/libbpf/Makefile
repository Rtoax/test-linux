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

KSYM_DO_EXECVEAT_COMMON := $(shell grep 't do_execveat_common' /proc/kallsyms \
			| head -1 \
			| awk '{print $$3}')

$(info KSYM_DO_EXECVEAT_COMMON = ${KSYM_DO_EXECVEAT_COMMON})

CC := gcc
CLANG := clang
BPFTOOL := bpftool

kconfig-obj-y :=
kconfig-obj-$(CONFIG_KPROBES) += kprobe
kconfig-obj-$(CONFIG_TRACEPOINTS) += tracepoint raw_tracepoint
kconfig-obj-$(CONFIG_PERF_EVENTS) += perf_event

$(info kconfig-obj-y : $(kconfig-obj-y))

ifneq ($(kconfig-obj-),)
  $(warning Not support ${kconfig-obj-})
endif

TARGETS :=
TARGETS += config-map
TARGETS += socket_filter
TARGETS += tc
TARGETS += xdp
TARGETS += sockops
TARGETS += $(kconfig-obj-y)

# _if_ there are no user mode code, append to bpf target only
TARGETS_BPF := ${TARGETS:=.bpf.o}
TARGETS_BPF += cgroup_skb.bpf.o
TARGETS_BPF += cgroup_sock.bpf.o
TARGETS_BPF += lwt_in.bpf.o

# Never append to skel target, always generate by bpf target
TARGETS_SKEL := $(patsubst %.bpf.o,%.skel.h,$(TARGETS_BPF))

CFLAGS_BPF := -I.
CFLAGS_BPF += -O2 -Wall -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += -D__TARGET_ARCH_$(ARCH)

CFLAGS := -lbpf
CFLAGS += -O0 -Wall -g
LDFLAGS := -lbpf
LDFLAGS += -O0 -Wall -g

CFLAGS_kprobe := -D'KSYM_DO_EXECVEAT_COMMON="${KSYM_DO_EXECVEAT_COMMON}"'
CFLAGS_BPF_kprobe := -D'KSYM_DO_EXECVEAT_COMMON="${KSYM_DO_EXECVEAT_COMMON}"'
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

%.bpf.o: %.bpf.c vmlinux.h
	@echo -e "  BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

%.skel.h: %.bpf.o
	@echo -e "  SKEL  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(BPFTOOL) gen skeleton $< > $@

%.o: %.c %.skel.h
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %: %.o
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

vmlinux.h:
	@echo -e "  BPFTOOL  \033[1m$(@)\033[m"
	${Q}${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

.PHONY: clean
clean:
	@echo -e "  RM  \033[1;32m$(TARGETS_BPF) ${TARGETS}\033[m"
	${Q}rm -f ${TARGETS_BPF} ${TARGETS} *.o *.skel.h vmlinux.h
