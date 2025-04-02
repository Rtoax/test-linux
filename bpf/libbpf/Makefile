# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk
include ../../kernel.mk

OUTPUT := $(abspath .output)
VIRT_TYPE ?= $(shell systemd-detect-virt)

include ../../kconfig.mk
include ../bpf.mk
include ./libbpf.mk

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
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_socket_sendmsg

$(info kconfig-obj-y : $(kconfig-obj-y))
$(info kconfig-obj-n : $(kconfig-obj-))

TARGETS :=
TARGETS += config-map
TARGETS += socket_filter
TARGETS += tc
TARGETS += xdp xdp_devmap xdp_simple xdp_dos
# kernel v5.8-rc4-1449-g9216477449f3
# commit 9216477449f3 ("bpf: cpumap: Add the possibility to attach an eBPF program to cpumap")
# struct bpf_cpumap_val support bpf_prog field
# kernel v5.8-rc4-1448-g644bfe51fa49
# commit 644bfe51fa49 ("cpumap: Formalize map value as a named struct")
# introduce struct bpf_cpumap_val
ifeq ($(call kernel_newer_than,5,8,0),y)
  TARGETS += xdp_cpumap
endif
TARGETS += sockops
TARGETS += sk_skb
TARGETS += sk_msg
TARGETS += cgroup_device
TARGETS += cgroup_sysctl
TARGETS += fmod_ret
ifeq ($(call kernel_newer_than,5,7,0),y)
  # linux v5.7-rc2-1180-geaaacd23910f
  # commit eaaacd23910f ("bpf: Add task and task/file iterator targets")
  TARGETS += iter_task iter_task_file
  # linux v5.7-rc2-1178-g6086d29def80
  # commit 6086d29def80 ("bpf: Add bpf_map iterator")
  TARGETS += iter_bpf_map
endif
ifeq ($(call kernel_newer_than,5,11,0),y)
  # linux v5.11-rc4-606-g3a7b35b899de
  # commit 3a7b35b899de ("bpf: Introduce task_vma bpf_iter")
  TARGETS += iter_task_vma
endif
ifeq ($(call kernel_newer_than,6,11,0),y)
  # linux v6.12-rc1-177-g4971266e1595
  # commit 4971266e1595 ("bpf: Add kmem_cache iterator")
  TARGETS += iter_kmem_cache
endif
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
TARGETS_BPF += map_arena.bpf.o
TARGETS_BPF += map_bloom_filter.bpf.o
TARGETS_BPF += sched_cls.bpf.o
TARGETS_BPF += sched_act.bpf.o
# Must be the last one
TARGETS_BPF := $(addprefix ${OUTPUT}/,${TARGETS_BPF})

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
ifeq ($(CONFIG_ARCH_HAS_SYSCALL_WRAPPER),y)
  CFLAGS_BPF += -DCONFIG_ARCH_HAS_SYSCALL_WRAPPER=1
endif

CFLAGS := -lbpf
CFLAGS += -O0 -Wall -g
LDFLAGS := -lbpf
LDFLAGS += -O0 -Wall -g
LDFLAGS += -pthread

CFLAGS += -DCONFIG_BPF_SYSCALL=$(CONFIG_BPF_SYSCALL)
CFLAGS += -DUID=$(UID)
CFLAGS_BPF += -DUID=$(UID)

CFLAGS += $(KFLAGS)
CFLAGS_BPF += $(KFLAGS)
CFLAGS += $(CFLAG_BPF_TARGET_ARCH)
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

# libbpf commit 8ade99a6f84d ("libbpf: Make libbpf_version.h non-auto-generated")
# v0.6.0 add macro LIBBPF_MAJOR_VERSION and LIBBPF_MINOR_VERSION in libbpf_version.h
CFLAGS += -DLIB_LIBBPF_MAJOR_VERSION=${LIBBPF_MAJOR_VERSION}
CFLAGS += -DLIB_LIBBPF_MINOR_VERSION=${LIBBPF_MINOR_VERSION}

ifdef DEBUG
  CFLAGS += -DDEBUG=1
  CFLAGS_BPF += -DDEBUG=1
  CLANG_V = -v
endif

CFLAGS += -I${OUTPUT}
CFLAGS_BPF += -I${OUTPUT}

CFLAGS_kprobe := -D'KSYM_DO_EXECVEAT_COMMON="${KSYM_DO_EXECVEAT_COMMON}"' -DKPROBE=1
CFLAGS_BPF_kprobe := -D'KSYM_DO_EXECVEAT_COMMON="${KSYM_DO_EXECVEAT_COMMON}"' -DKPROBE=1
ifeq ($(CONFIG_BPF_KPROBE_OVERRIDE),y)
  CFLAGS_BPF_kprobe += -DCONFIG_BPF_KPROBE_OVERRIDE=1
else
  $(warning "Not config CONFIG_BPF_KPROBE_OVERRIDE=y, skip test bpf_override_return()")
endif
CFLAGS_fentry := -DFENTRY=1
CFLAGS_BPF_fentry := ${CFLAGS_fentry}
CFLAGS_fmod_ret := -DFMOD_RET=1
CFLAGS_BPF_fmod_ret := ${CFLAGS_fmod_ret}
CFLAGS_socket_filter := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_ARRAY=1
CFLAGS_BPF_socket_filter := ${CFLAGS_socket_filter}
CFLAGS_tracepoint := -DMAP_HASH -DTRACEPOINT=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_tracepoint := ${CFLAGS_tracepoint}
# Kill process with signal.
CFLAGS_BPF_tracepoint += -DBPF_SEND_SIGNAL=1
CFLAGS_raw_tracepoint := -DSEC_DEF_RAW_TRACEPOINT=1
CFLAGS_BPF_raw_tracepoint := ${CFLAGS_raw_tracepoint}
CFLAGS_tp_btf := -DSEC_DEF_TP_BTF=1
CFLAGS_BPF_tp_btf := ${CFLAGS_tp_btf}
CFLAGS_xdp := -DSTRICT_SEC_NAME=1 -DXDP_BASIC=1 -DXDP_BASIC_DUMMY=1 -DXDP_BASIC_TX=1 -DXDP_BASIC_PRINTK=1
CFLAGS_BPF_xdp := ${CFLAGS_xdp}
CFLAGS_xdp_devmap := -DSTRICT_SEC_NAME=1 -DXDP_DEVMAP=1
CFLAGS_BPF_xdp_devmap := ${CFLAGS_xdp_devmap}
CFLAGS_xdp_cpumap := -DSTRICT_SEC_NAME=1 -DXDP_CPUMAP=1
CFLAGS_BPF_xdp_cpumap := ${CFLAGS_xdp_cpumap}
CFLAGS_xdp_xskmap := -DSTRICT_SEC_NAME=1 -DXDP_XSKMAP=1
CFLAGS_BPF_xdp_xskmap := ${CFLAGS_xdp_xskmap}
CFLAGS_iter_task := -DITER_TASK=1
CFLAGS_BPF_iter_task := ${CFLAGS_iter_task}
CFLAGS_iter_task_file := -DITER_TASK_FILE=1
CFLAGS_BPF_iter_task_file := ${CFLAGS_iter_task_file}
CFLAGS_iter_task_vma := -DITER_TASK_VMA=1
CFLAGS_BPF_iter_task_vma := ${CFLAGS_iter_task_vma}
CFLAGS_iter_bpf_map := -DITER_BPF_MAP=1
CFLAGS_BPF_iter_bpf_map := ${CFLAGS_iter_bpf_map}
CFLAGS_iter_kmem_cache := -DITER_KMEM_CACHE=1
CFLAGS_BPF_iter_kmem_cache := ${CFLAGS_iter_kmem_cache}
CFLAGS_lsm_bpf := -DLSM_BPF=1
CFLAGS_BPF_lsm_bpf := ${CFLAGS_lsm_bpf}
CFLAGS_lsm_socket_create := -DLSM_SOCKET_CREATE=1
CFLAGS_BPF_lsm_socket_create := ${CFLAGS_lsm_socket_create}
CFLAGS_lsm_socket_sendmsg := -DLSM_SOCKET_SENDMSG=1
CFLAGS_BPF_lsm_socket_sendmsg := ${CFLAGS_BPF_lsm_socket_sendmsg}
CFLAGS_BPF_sched_act := -DTEST_SCHED_ACT=1

CFLAGS_map_hash := ${CFLAGS_tracepoint}
CFLAGS_BPF_map_hash := ${CFLAGS_BPF_tracepoint}
CFLAGS_map_percpu_hash := -DTRACEPOINT=1 -DMAP_PERCPU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_percpu_hash := ${CFLAGS_map_percpu_hash}
CFLAGS_map_lru_hash := -DTRACEPOINT=1 -DMAP_LRU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_lru_hash := ${CFLAGS_map_lru_hash}
CFLAGS_map_lru_percpu_hash := -DTRACEPOINT=1 -DMAP_LRU_PERCPU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_lru_percpu_hash := ${CFLAGS_map_lru_percpu_hash}
CFLAGS_map_array := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_ARRAY=1
CFLAGS_BPF_map_array := ${CFLAGS_map_array}
CFLAGS_map_percpu_array := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_PERCPU_ARRAY=1
CFLAGS_BPF_map_percpu_array := ${CFLAGS_map_percpu_array}
CFLAGS_map_array_of_maps := -DMAP_ARRAY_OF_MAPS=1
CFLAGS_BPF_map_array_of_maps := ${CFLAGS_map_array_of_maps}
CFLAGS_map_hash_of_maps := -DMAP_HASH_OF_MAPS=1
CFLAGS_BPF_map_hash_of_maps := ${CFLAGS_map_hash_of_maps}
CFLAGS_BPF_map_ringbuf := -DMAP_ARRAY=1
CFLAGS_BPF_map_devmap := ${CFLAGS_BPF_xdp_devmap}

SOCKET_HELPERS := ${OUTPUT}/socket_helpers.o
TASK_HELPERS := ${OUTPUT}/task_helpers.o
TRACE_HELPERS := ${OUTPUT}/trace_helpers.o
LIBBPF_WRAPPER := ${OUTPUT}/libbpf_wrapper.o
LIBXDP_HELPERS := ${OUTPUT}/libxdp_helpers.o


.PHONY: build
build: libbpf_version vmlinux.h ${TARGETS_BPF} ${TARGETS_SKEL} ${TARGETS}
	${Q}./libbpf_version | sed 's/^/  /g'
	@echo -e "  \033[1;33mDone\033[m"

${OUTPUT}/socket_helpers.o: socket_helpers.h
${OUTPUT}/trace_helpers.o: trace_helpers.h
${OUTPUT}/task_helpers.o: task_helpers.h
${OUTPUT}/libbpf_wrapper.o: libbpf_wrapper.h
${OUTPUT}/libxdp_helpers.o: libxdp_helpers.h
${OUTPUT}/libbpf_version: ${OUTPUT}/libbpf_version.o

config-map: ${OUTPUT}/config-map.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
socket_filter: ${OUTPUT}/socket_filter.o ${SOCKET_HELPERS}
tc: ${OUTPUT}/tc.o ${TRACE_HELPERS}
xdp: ${OUTPUT}/xdp.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
xdp_simple: ${OUTPUT}/xdp_simple.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER} ${LIBXDP_HELPERS}
xdp_dos: ${OUTPUT}/xdp_dos.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER} ${LIBXDP_HELPERS}
xdp_devmap: ${OUTPUT}/xdp_devmap.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
xdp_cpumap: ${OUTPUT}/xdp_cpumap.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
xdp_xskmap: ${OUTPUT}/xdp_xskmap.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER} ${LIBXDP_HELPERS}
sockops: ${OUTPUT}/sockops.o ${TRACE_HELPERS}
kprobe: ${OUTPUT}/kprobe.o ${TRACE_HELPERS}
tracepoint: ${OUTPUT}/tracepoint.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
raw_tracepoint: ${OUTPUT}/raw_tracepoint.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
tp_btf: ${OUTPUT}/tp_btf.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
perf_event: ${OUTPUT}/perf_event.o
sk_skb: ${OUTPUT}/sk_skb.o
sk_msg: ${OUTPUT}/sk_msg.o
cgroup_device: ${OUTPUT}/cgroup_device.o ${TRACE_HELPERS}
cgroup_sysctl: ${OUTPUT}/cgroup_sysctl.o ${TRACE_HELPERS}
fentry: ${OUTPUT}/fentry.o ${TRACE_HELPERS}
fmod_ret: ${OUTPUT}/fmod_ret.o ${TRACE_HELPERS}
iter_task: ${OUTPUT}/iter_task.o ${TASK_HELPERS}
iter_task_file: ${OUTPUT}/iter_task_file.o
iter_task_vma: ${OUTPUT}/iter_task_vma.o
iter_bpf_map: ${OUTPUT}/iter_bpf_map.o
iter_kmem_cache: ${OUTPUT}/iter_kmem_cache.o
lsm_bpf: ${OUTPUT}/lsm_bpf.o ${TRACE_HELPERS}
lsm_socket_create: ${OUTPUT}/lsm_socket_create.o ${TRACE_HELPERS}
lsm_socket_sendmsg: ${OUTPUT}/lsm_socket_sendmsg.o ${TRACE_HELPERS}

map_hash: ${OUTPUT}/map_hash.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
map_percpu_hash: ${OUTPUT}/map_percpu_hash.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
map_lru_hash: ${OUTPUT}/map_lru_hash.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
map_lru_percpu_hash: ${OUTPUT}/map_lru_percpu_hash.o ${TRACE_HELPERS} ${LIBBPF_WRAPPER}
map_array: ${OUTPUT}/map_array.o ${SOCKET_HELPERS}
map_percpu_array: ${OUTPUT}/map_percpu_array.o ${SOCKET_HELPERS}

${OUTPUT}:
	@echo -e "  MKDIR  \033[1m$(notdir ${@})\033[m"
	${Q}mkdir -p $(@)

${OUTPUT}/%.bpf.o: %.bpf.c vmlinux.h | ${OUTPUT}
	@echo -e "  BPF  \033[1m$(notdir ${@})\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*)) $(CLANG_V) $(shell ./libbpf_version cflags)

${OUTPUT}/%.skel.h: ${OUTPUT}/%.bpf.o | ${OUTPUT}
	@echo -e "  SKEL  \033[1m$(notdir ${@})\033[m"
	${Q}$(BPFTOOL) gen skeleton $(GEN_SKEL_ARGS) $(GEN_SKEL_ARGS_$(*)) $< > $@

${OUTPUT}/%.o: %.c ${OUTPUT}/%.skel.h | ${OUTPUT}
	@echo -e "  CC  \033[1m$(notdir ${@})\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}/%.o: %.c | ${OUTPUT}
	@echo -e "  CC(LIB)  \033[1m$(notdir ${@})\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS) libbpf_version: %: ${OUTPUT}/%.o
	@echo -e "  LD  \033[1;32m$(notdir ${@})\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

include ../bpftool/vmlinux.h.mk

.PHONY: clean
clean:
	@echo -e "  RM  \033[1;32m$(TARGETS_BPF) ${TARGETS}\033[m"
	${Q}rm -f ${TARGETS_BPF} ${TARGETS} *.o *.skel.h vmlinux.h libbpf_version
	${Q}rm -rf ${OUTPUT}
