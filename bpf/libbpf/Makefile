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

UID=$(shell id -u)

CC := gcc
CLANG := clang
BPFTOOL := bpftool

kconfig-obj-y :=
kconfig-obj-$(CONFIG_KPROBES) += kprobe
kconfig-obj-$(CONFIG_TRACEPOINTS) += tracepoint raw_tracepoint tp_btf
kconfig-obj-$(CONFIG_PERF_EVENTS) += perf_event
# fentry: -pg -mfentry
#  fentry + BPF trampoline ~= kprobe hook
kconfig-obj-$(CONFIG_HAVE_FENTRY) += fentry
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_bpf
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_socket_create

$(info kconfig-obj-y : $(kconfig-obj-y))
$(info kconfig-obj-n : $(kconfig-obj-))

TARGETS :=
TARGETS += config-map
TARGETS += socket_filter
TARGETS += tc
TARGETS += xdp
TARGETS += sockops
TARGETS += sk_skb
TARGETS += sk_msg
TARGETS += cgroup_device
TARGETS += cgroup_sysctl
TARGETS += fmod_ret
TARGETS += iter_task
TARGETS += iter_task_file
TARGETS += iter_task_vma
TARGETS += iter_bpf_map
TARGETS += $(kconfig-obj-y)

# _if_ there are no user mode code, append to bpf target only
TARGETS_BPF := ${TARGETS:=.bpf.o}
TARGETS_BPF += cgroup_skb.bpf.o
TARGETS_BPF += cgroup_sock.bpf.o
TARGETS_BPF += cgroup_sock_addr.bpf.o
TARGETS_BPF += cgroup_sockopt.bpf.o
TARGETS_BPF += lwt_in.bpf.o
TARGETS_BPF += lwt_out.bpf.o
TARGETS_BPF += lwt_xmit.bpf.o
TARGETS_BPF += sk_lookup.bpf.o
TARGETS_BPF += flow_dissector.bpf.o
TARGETS_BPF += sk_reuseport.bpf.o
TARGETS_BPF += netfilter.bpf.o

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

CFLAGS += -DCONFIG_BPF_SYSCALL=$(CONFIG_BPF_SYSCALL)
CFLAGS += -DUID=$(UID)
CFLAGS_BPF += -DUID=$(UID)

ifdef DEBUG
  CFLAGS += -DDEBUG=1
  CFLAGS_BPF += -DDEBUG=1
  CLANG_V = -v
endif

CFLAGS_kprobe := -D'KSYM_DO_EXECVEAT_COMMON="${KSYM_DO_EXECVEAT_COMMON}"' -DKPROBE=1
CFLAGS_BPF_kprobe := -D'KSYM_DO_EXECVEAT_COMMON="${KSYM_DO_EXECVEAT_COMMON}"' -DKPROBE=1
CFLAGS_fentry := -DFENTRY=1
CFLAGS_BPF_fentry := -DFENTRY=1
CFLAGS_fmod_ret := -DFMOD_RET=1
CFLAGS_BPF_fmod_ret := -DFMOD_RET=1
CFLAGS_socket_filter := -DSTRICT_SEC_NAME=1
CFLAGS_BPF_socket_filter := -DSTRICT_SEC_NAME=1
CFLAGS_tracepoint := -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_tracepoint := -DSEC_DEF_TRACEPOINT=1
CFLAGS_raw_tracepoint := -DSEC_DEF_RAW_TRACEPOINT=1
CFLAGS_BPF_raw_tracepoint := -DSEC_DEF_RAW_TRACEPOINT=1
CFLAGS_tp_btf := -DSEC_DEF_TP_BTF=1
CFLAGS_BPF_tp_btf := -DSEC_DEF_TP_BTF=1
CFLAGS_xdp := -DSTRICT_SEC_NAME=1
CFLAGS_BPF_xdp := -DSTRICT_SEC_NAME=1
CFLAGS_iter_task := -DITER_TASK=1
CFLAGS_BPF_iter_task := -DITER_TASK=1
CFLAGS_iter_task_file := -DITER_TASK_FILE=1
CFLAGS_BPF_iter_task_file := -DITER_TASK_FILE=1
CFLAGS_iter_task_vma := -DITER_TASK_VMA=1
CFLAGS_BPF_iter_task_vma := -DITER_TASK_VMA=1
CFLAGS_iter_bpf_map := -DITER_BPF_MAP=1
CFLAGS_BPF_iter_bpf_map := -DITER_BPF_MAP=1
CFLAGS_lsm_bpf := -DLSM_BPF=1
CFLAGS_BPF_lsm_bpf := -DLSM_BPF=1
CFLAGS_lsm_socket_create := -DLSM_SOCKET_CREATE=1
CFLAGS_BPF_lsm_socket_create := -DLSM_SOCKET_CREATE=1

TRACE_HELPERS := trace_helpers.o


.PHONY: build
build: vmlinux.h ${TARGETS_BPF} ${TARGETS_SKEL} ${TARGETS}

config-map: config-map.o
socket_filter: socket_filter.o
tc: tc.o ${TRACE_HELPERS}
xdp: xdp.o
sockops: sockops.o ${TRACE_HELPERS}
kprobe: kprobe.o ${TRACE_HELPERS}
tracepoint: tracepoint.o
raw_tracepoint: raw_tracepoint.o
perf_event: perf_event.o
sk_skb: sk_skb.o
sk_msg: sk_msg.o
cgroup_device: cgroup_device.o ${TRACE_HELPERS}
cgroup_sysctl: cgroup_sysctl.o ${TRACE_HELPERS}
fentry: fentry.o ${TRACE_HELPERS}
fmod_ret: fmod_ret.o ${TRACE_HELPERS}
iter_task: iter_task.o
iter_task_file: iter_task_file.o
iter_task_vma: iter_task_vma.o
iter_bpf_map: iter_bpf_map.o
lsm_bpf: lsm_bpf.o ${TRACE_HELPERS}
lsm_socket_create: lsm_socket_create.o ${TRACE_HELPERS}

%.bpf.o: %.bpf.c vmlinux.h
	@echo -e "  BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*)) $(CLANG_V)

%.skel.h: %.bpf.o
	@echo -e "  SKEL  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(BPFTOOL) gen skeleton $< > $@

%.o: %.c %.skel.h
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.o: %.c
	@echo -e "  CC(LIB)  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
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
