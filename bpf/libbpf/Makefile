# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

VIRT_TYPE ?= $(shell systemd-detect-virt)
CONFIG_KERNEL ?= /boot/config-$(shell uname -r)

# If don't have kernel config, enable all CONFIG_=y, otherwise, include config
# file.
ifeq ($(wildcard $(CONFIG_KERNEL)),)
  $(warning "WARNING: Not found ${CONFIG_KERNEL}, config all to =y")
  CONFIG_KPROBES=y
  CONFIG_TRACEPOINTS=y
  CONFIG_PERF_EVENTS=y
  CONFIG_HAVE_FENTRY=y
  CONFIG_BPF_LSM=y
  CONFIG_BPF_SYSCALL=y
  CONFIG_BPF_KPROBE_OVERRIDE=
else
  include $(CONFIG_KERNEL)
endif

include ../bpf.mk

KSYM_DO_EXECVEAT_COMMON := $(shell grep 't do_execveat_common' /proc/kallsyms \
			| head -1 \
			| awk '{print $$3}')

$(info KSYM_DO_EXECVEAT_COMMON = ${KSYM_DO_EXECVEAT_COMMON})

UID=$(shell id -u)

CC := gcc
CLANG := clang
BPFTOOL := bpftool
# bpftool gen skeleton
GEN_SKEL_ARGS :=

kconfig-obj-y :=
kconfig-obj-$(CONFIG_KPROBES) += kprobe
kconfig-obj-$(CONFIG_TRACEPOINTS) += tracepoint raw_tracepoint tp_btf
kconfig-obj-$(CONFIG_TRACEPOINTS) += map_hash map_lru_hash map_percpu_hash map_lru_percpu_hash
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
TARGETS += xdp xdp_devmap xdp_cpumap
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
TARGETS += map_array map_percpu_array
TARGETS += xdp_xskmap

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
TARGETS_BPF += syscall.bpf.o
TARGETS_BPF += map_queue.bpf.o
TARGETS_BPF += map_stack.bpf.o
TARGETS_BPF += map_lpm_trie.bpf.o
TARGETS_BPF += map_array_of_maps.bpf.o
TARGETS_BPF += map_hash_of_maps.bpf.o
TARGETS_BPF += map_ringbuf.bpf.o
TARGETS_BPF += map_devmap.bpf.o

# Never append to skel target, always generate by bpf target
TARGETS_SKEL := $(patsubst %.bpf.o,%.skel.h,$(TARGETS_BPF))

ifeq (${VIRT_TYPE},systemd-nspawn)
  $(warning "Could not support vmlinux.h in systemd-nspawn")
  TARGETS :=
  TARGETS_BPF :=
  TARGETS_SKEL :=
endif

CFLAGS_BPF := -I.
CFLAGS_BPF += -O2 -Wall -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

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
ifeq ($(CONFIG_BPF_KPROBE_OVERRIDE),y)
  CFLAGS_BPF_kprobe += -DBPF_OVERRIDE_RETURN=1
else
  $(warning "Not config CONFIG_BPF_KPROBE_OVERRIDE=y, skip test bpf_override_return()")
endif
CFLAGS_fentry := -DFENTRY=1
CFLAGS_BPF_fentry := -DFENTRY=1
CFLAGS_fmod_ret := -DFMOD_RET=1
CFLAGS_BPF_fmod_ret := -DFMOD_RET=1
CFLAGS_socket_filter := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_ARRAY=1
CFLAGS_BPF_socket_filter := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_ARRAY=1
CFLAGS_tracepoint := -DMAP_HASH -DTRACEPOINT=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_tracepoint := -DMAP_HASH -DTRACEPOINT=1 -DSEC_DEF_TRACEPOINT=1
# Kill process with signal.
CFLAGS_BPF_tracepoint += -DBPF_SEND_SIGNAL=1
CFLAGS_raw_tracepoint := -DSEC_DEF_RAW_TRACEPOINT=1
CFLAGS_BPF_raw_tracepoint := -DSEC_DEF_RAW_TRACEPOINT=1
CFLAGS_tp_btf := -DSEC_DEF_TP_BTF=1
CFLAGS_BPF_tp_btf := -DSEC_DEF_TP_BTF=1
CFLAGS_xdp := -DSTRICT_SEC_NAME=1 -DXDP_BASIC=1
CFLAGS_BPF_xdp := -DSTRICT_SEC_NAME=1 -DXDP_BASIC=1
CFLAGS_xdp_devmap := -DSTRICT_SEC_NAME=1 -DXDP_DEVMAP=1
CFLAGS_BPF_xdp_devmap := -DSTRICT_SEC_NAME=1 -DXDP_DEVMAP=1
CFLAGS_xdp_cpumap := -DSTRICT_SEC_NAME=1 -DXDP_CPUMAP=1
CFLAGS_BPF_xdp_cpumap := -DSTRICT_SEC_NAME=1 -DXDP_CPUMAP=1
CFLAGS_xdp_xskmap := -DSTRICT_SEC_NAME=1 -DXDP_XSKMAP=1
CFLAGS_BPF_xdp_xskmap := -DSTRICT_SEC_NAME=1 -DXDP_XSKMAP=1
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

CFLAGS_map_hash := ${CFLAGS_tracepoint}
CFLAGS_BPF_map_hash := ${CFLAGS_BPF_tracepoint}
CFLAGS_map_percpu_hash := -DTRACEPOINT=1 -DMAP_PERCPU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_percpu_hash := -DTRACEPOINT=1 -DMAP_PERCPU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_map_lru_hash := -DTRACEPOINT=1 -DMAP_LRU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_lru_hash := -DTRACEPOINT=1 -DMAP_LRU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_map_lru_percpu_hash := -DTRACEPOINT=1 -DMAP_LRU_PERCPU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_lru_percpu_hash := -DTRACEPOINT=1 -DMAP_LRU_PERCPU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_map_array := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_ARRAY=1
CFLAGS_BPF_map_array := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_ARRAY=1
CFLAGS_map_percpu_array := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_PERCPU_ARRAY=1
CFLAGS_BPF_map_percpu_array := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_PERCPU_ARRAY=1
CFLAGS_map_array_of_maps := -DMAP_ARRAY_OF_MAPS=1
CFLAGS_BPF_map_array_of_maps := -DMAP_ARRAY_OF_MAPS=1
CFLAGS_map_hash_of_maps := -DMAP_HASH_OF_MAPS=1
CFLAGS_BPF_map_hash_of_maps := -DMAP_HASH_OF_MAPS=1
CFLAGS_BPF_map_ringbuf := -DMAP_ARRAY=1
CFLAGS_BPF_map_devmap := ${CFLAGS_BPF_xdp_devmap}

GEN_SKEL_ARGS_syscall := -L

SOCKET_HELPERS := socket_helpers.o
TASK_HELPERS := task_helpers.o
TRACE_HELPERS := trace_helpers.o
LIBBPF_WRAPPER := libbpf_wrapper.o
LIBXDP_HELPERS := libxdp_helpers.o


.PHONY: build
build: libbpf_version vmlinux.h ${TARGETS_BPF} ${TARGETS_SKEL} ${TARGETS}
	${Q}./libbpf_version | sed 's/^/  /g'
	@echo -e "  \033[1;33mDone\033[m"

libbpf_version: libbpf_version.o

config-map: config-map.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
socket_filter: socket_filter.o ${SOCKET_HELPERS}
tc: tc.o ${TRACE_HELPERS}
xdp: xdp.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
xdp_devmap: xdp_devmap.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
xdp_cpumap: xdp_cpumap.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
xdp_xskmap: xdp_xskmap.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER} ${LIBXDP_HELPERS}
sockops: sockops.o ${TRACE_HELPERS}
kprobe: kprobe.o ${TRACE_HELPERS}
tracepoint: tracepoint.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
raw_tracepoint: raw_tracepoint.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
tp_btf: tp_btf.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
perf_event: perf_event.o
sk_skb: sk_skb.o
sk_msg: sk_msg.o
cgroup_device: cgroup_device.o ${TRACE_HELPERS}
cgroup_sysctl: cgroup_sysctl.o ${TRACE_HELPERS}
fentry: fentry.o ${TRACE_HELPERS}
fmod_ret: fmod_ret.o ${TRACE_HELPERS}
iter_task: iter_task.o ${TASK_HELPERS}
iter_task_file: iter_task_file.o
iter_task_vma: iter_task_vma.o
iter_bpf_map: iter_bpf_map.o
lsm_bpf: lsm_bpf.o ${TRACE_HELPERS}
lsm_socket_create: lsm_socket_create.o ${TRACE_HELPERS}

map_hash: map_hash.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
map_percpu_hash: map_percpu_hash.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
map_lru_hash: map_lru_hash.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
map_lru_percpu_hash: map_lru_percpu_hash.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
map_array: map_array.o ${SOCKET_HELPERS}
map_percpu_array: map_percpu_array.o ${SOCKET_HELPERS}

%.bpf.o: %.bpf.c vmlinux.h
	@echo -e "  BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*)) $(CLANG_V) $(shell ./libbpf_version cflags)

%.skel.h: %.bpf.o
	@echo -e "  SKEL  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(BPFTOOL) gen skeleton $(GEN_SKEL_ARGS_$(*)) $< > $@

%.o: %.c %.skel.h
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.o: %.c
	@echo -e "  CC(LIB)  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS) libbpf_version: %: %.o
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

vmlinux.h:
	@echo -e "  BPFTOOL  \033[1m$(@)\033[m"
	${Q}${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

.PHONY: clean
clean:
	@echo -e "  RM  \033[1;32m$(TARGETS_BPF) ${TARGETS}\033[m"
	${Q}rm -f ${TARGETS_BPF} ${TARGETS} *.o *.skel.h vmlinux.h libbpf_version
