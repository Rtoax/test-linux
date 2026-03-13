# SPDX-License-Identifier: GPL-3.0
include kernel.mk
ifndef NO_PAHOLE
  include pahole.mk
endif

include kconfig.mk
include helpers.mk
include bpf/bpf.mk
include ldconfig.mk
include bpf/btf.mk
include bpf/helper.mk
include bpf/iter.mk
include bpf/libbpf.mk
include bpf/bpftool.mk

LIBBPF_TRACE_HELPERS := libtrace_helpers.so
HELPERS := ${OUTPUT}task_helpers.o \
	${OUTPUT}stack_helpers.o \
	${OUTPUT}libbpf_wrapper.o \
	${OUTPUT}libxdp_helpers.o \
	${LIBBPF_TRACE_HELPERS} \
	${SOCKET_HELPERS} \
	${KSYM_HELPERS}

KSYM_DO_EXECVEAT_COMMON := $(shell grep -w 't do_execveat_common' /proc/kallsyms \
			| grep -v cold \
			| head -1 \
			| awk '{print $$3}')

ifdef DEBUG
  $(info KSYM_DO_EXECVEAT_COMMON = ${KSYM_DO_EXECVEAT_COMMON})
endif

kobjs-y :=
kobjs-$(CONFIG_KPROBES) += kprobe
kobjs-$(CONFIG_TRACEPOINTS) += tracepoint raw_tracepoint tp_btf
kobjs-$(CONFIG_TRACEPOINTS) += map_hash map_lru_hash map_percpu_hash map_lru_percpu_hash
kobjs-$(CONFIG_PERF_EVENTS) += perf_event perf_buffer
# fentry: -pg -mfentry
#  fentry + BPF trampoline ~= kprobe hook
kobjs-$(CONFIG_HAVE_FENTRY) += fentry
kobjs-$(CONFIG_BPF_LSM) += lsm_bpf
kobjs-$(CONFIG_BPF_LSM) += lsm_socket_create
kobjs-$(CONFIG_BPF_LSM) += lsm_socket_sendmsg
kobjs-$(CONFIG_BPF_LSM) += lsm_file_open
kobjs-$(CONFIG_RING_BUFFER) += ring_buffer

ifdef DEBUG
  $(info kobjs-y : $(kobjs-y))
  $(info kobjs-n : $(kobjs-))
endif

target-y := config-map
target-y += socket_filter
target-y += tc
target-y += xdp xdp_simple xdp_dos
# kernel v4.12-11037-g546ac1ffb70d
# commit 546ac1ffb70d ("bpf: add devmap, a map for storing net device references")
target-$(call kver_gt,4,12,0) += xdp_devmap
# kernel v5.8-rc4-1449-g9216477449f3
# commit 9216477449f3 ("bpf: cpumap: Add the possibility to attach an eBPF program to cpumap")
# struct bpf_cpumap_val support bpf_prog field
# kernel v5.8-rc4-1448-g644bfe51fa49
# commit 644bfe51fa49 ("cpumap: Formalize map value as a named struct")
# introduce struct bpf_cpumap_val
target-$(call kver_gt,5,8,0) += xdp_cpumap

target-y += sockops
target-y += sk_skb
target-y += sk_msg
target-y += cgroup_device
target-y += cgroup_sysctl
target-y += fmod_ret
target-${SUPPORT_ITER_TASK} += iter_task
target-${SUPPORT_ITER_TASK_FILE} += iter_task_file
target-${SUPPORT_ITER_BPF_MAP} += iter_bpf_map
target-${SUPPORT_ITER_TASK_VMA} += iter_task_vma
target-${SUPPORT_ITER_KMEM_CACHE} += iter_kmem_cache
target-y += $(kobjs-y)
target-y += map_array map_prog_array map_percpu_array
target-y += xdp_xskmap

CFLAGS_BPF += ${bpf-helper-cflags}

# linux commit bd1279ae8a69 ("bpf: Add bpf_rbtree_{add,remove,first} kfuncs")
# v6.2-rc7-1572-gbd1279ae8a69
ifeq ($(call kver_gt,6,2,0),y)
  # linux commit 9c395c1b99bd ("bpf: Add basic bpf_rb_{root,node} support")
  # v6.2-rc7-1571-g9c395c1b99bd add bpf_rb_root to uapi/linux/bpf.h
  ifeq ($(call kver_uapi_lt,6,2,0),y)
    $(warning "kuapi not support bpf_rb_root")
    CFLAGS += -DKAPI_NO_BPF_RB_ROOT=1
  endif
  target-y += rbtree
  target-y += rbtree-raw-map
endif

# linux commit d83525ca62cf ("bpf: introduce bpf_spin_lock")
# v5.0-rc4-620-gd83525ca62cf
target-$(call kver_gt,5,0,0) += spin_lock

# _if_ there are no user mode code, append to bpf target only
obj-bpf.o := ${target-y:=.bpf.o}
obj-bpf.o += cgroup_skb.bpf.o
obj-bpf.o += cgroup_sock.bpf.o
obj-bpf.o += cgroup_sock_addr.bpf.o
obj-bpf.o += cgroup_sockopt.bpf.o
obj-bpf.o += lwt_in.bpf.o
obj-bpf.o += lwt_out.bpf.o
obj-bpf.o += lwt_xmit.bpf.o
obj-bpf.o += sk_lookup.bpf.o
obj-bpf.o += flow_dissector.bpf.o
obj-bpf.o += sk_reuseport.bpf.o
obj-bpf.o += netfilter.bpf.o
obj-bpf.o += syscall.bpf.o
obj-bpf.o += map_queue.bpf.o
obj-bpf.o += map_stack.bpf.o
obj-bpf.o += map_lpm_trie.bpf.o
obj-bpf.o += map_in_map.bpf.o
obj-bpf.o += map_ringbuf.bpf.o
obj-bpf.o += map_devmap.bpf.o
obj-bpf.o += map_arena.bpf.o
obj-bpf.o += map_bloom_filter.bpf.o
obj-bpf.o += sched_cls.bpf.o
obj-bpf.o += sched_act.bpf.o

target-bpf-y := $(addprefix ${OUTPUT},${obj-bpf.o})

target-libso-y := ${LIBBPF_TRACE_HELPERS}
libtrace_helpers.so-objs := ${OUTPUT}trace_helpers.so.o

target-prep-y += ${HELPERS}
target-post-y += $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))
target-post-y += $(patsubst %.bpf.o,%.bpf.s,$(target-bpf-y))
target-post-y += $(patsubst %.bpf.o,%.bpf.bc,$(target-bpf-y))

target-prog-y += version.sh version.sh.1 version.sh.2 version.sh.3

PROG_ARGS_version.sh.1 := --major
PROG_ARGS_version.sh.2 := --minor
PROG_ARGS_version.sh.3 := --patchlevel

$(foreach t, ${target-y}, $(eval ${t}-objs := ${HELPERS}))

ifeq ($(CONFIG_ARCH_HAS_SYSCALL_WRAPPER),y)
  CFLAGS_BPF += -DCONFIG_ARCH_HAS_SYSCALL_WRAPPER=1
endif

LDFLAGS := -lbpf
LDFLAGS += -pthread

CFLAGS += -DCONFIG_BPF_SYSCALL=$(CONFIG_BPF_SYSCALL)

CFLAGS += $(KFLAGS)
CFLAGS_BPF += $(KFLAGS)
CFLAGS += $(CFLAG_BPF_TARGET_ARCH)

ifdef DEBUG
  CLANG_V = -v
endif

CFLAGS += ${pahole-cflags}
CFLAGS_BPF += ${pahole-cflags}

CFLAGS_kprobe := -D'KSYM_DO_EXECVEAT_COMMON="${KSYM_DO_EXECVEAT_COMMON}"' -DKPROBE=1
CFLAGS_BPF_kprobe := -D'KSYM_DO_EXECVEAT_COMMON="${KSYM_DO_EXECVEAT_COMMON}"' -DKPROBE=1
ifeq ($(CONFIG_BPF_KPROBE_OVERRIDE),y)
  CFLAGS_BPF_kprobe += -DCONFIG_BPF_KPROBE_OVERRIDE=1
else
  ifdef DEBUG
    $(warning "Not config CONFIG_BPF_KPROBE_OVERRIDE=y, skip test bpf_override_return()")
  endif
endif
CFLAGS_fentry := -DFENTRY=1
CFLAGS_BPF_fentry := ${CFLAGS_fentry}
CFLAGS_fmod_ret := -DFMOD_RET=1
CFLAGS_BPF_fmod_ret := ${CFLAGS_fmod_ret}
CFLAGS_socket_filter := -DSOCKET_FILTER=1 -DMAP_ARRAY=1 -DRING_BUFFER=1
CFLAGS_BPF_socket_filter := ${CFLAGS_socket_filter}
CFLAGS_ring_buffer := ${CFLAGS_socket_filter} -DRING_BUFFER=1
CFLAGS_BPF_ring_buffer := ${CFLAGS_ring_buffer}
CFLAGS_tracepoint := -DMAP_HASH -DTRACEPOINT=1 -DSEC_DEF_TRACEPOINT=1 -DPARSE_AUXV=1
CFLAGS_BPF_tracepoint := ${CFLAGS_tracepoint}
# Kill process with signal.
CFLAGS_BPF_tracepoint += -DBPF_SEND_SIGNAL=1
CFLAGS_raw_tracepoint := -DSEC_DEF_RAW_TRACEPOINT=1
CFLAGS_BPF_raw_tracepoint := ${CFLAGS_raw_tracepoint}
CFLAGS_tp_btf := -DSEC_DEF_TP_BTF=1
CFLAGS_BPF_tp_btf := ${CFLAGS_tp_btf}
CFLAGS_xdp := -DXDP_BASIC=1 -DXDP_BASIC_DUMMY=1 -DXDP_BASIC_TX=1 -DXDP_BASIC_PRINTK=1
CFLAGS_BPF_xdp := ${CFLAGS_xdp}
CFLAGS_xdp_devmap := -DXDP_DEVMAP=1
ifeq ($(call vmlinux_has_struct_shell,bpf_devmap_val),y)
  CFLAGS_xdp_devmap += -DHAVE_STRUCT_BPF_DEVMAP_VAL=1
  $(info Found struct bpf_devmap_val{})
else
  $(warning not found struct bpf_devmap_val {})
endif
CFLAGS_BPF_xdp_devmap := ${CFLAGS_xdp_devmap}
CFLAGS_xdp_cpumap := -DXDP_CPUMAP=1
CFLAGS_BPF_xdp_cpumap := ${CFLAGS_xdp_cpumap}
CFLAGS_xdp_xskmap := -DXDP_XSKMAP=1
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
CFLAGS_LSM := -DIN_BPF_LSM=1
CFLAGS_lsm_bpf := ${CFLAGS_LSM} -DLSM_BPF=1
CFLAGS_BPF_lsm_bpf := ${CFLAGS_lsm_bpf}
CFLAGS_lsm_socket_create := ${CFLAGS_LSM} -DLSM_SOCKET_CREATE=1
CFLAGS_BPF_lsm_socket_create := ${CFLAGS_lsm_socket_create}
CFLAGS_lsm_socket_sendmsg := ${CFLAGS_LSM} -DLSM_SOCKET_SENDMSG=1
CFLAGS_BPF_lsm_socket_sendmsg := ${CFLAGS_lsm_socket_sendmsg}
CFLAGS_lsm_file_open := ${CFLAGS_LSM} -DLSM_FILE_OPEN=1
CFLAGS_BPF_lsm_file_open := ${CFLAGS_lsm_file_open}
CFLAGS_BPF_sched_act := -DTEST_SCHED_ACT=1

CFLAGS_perf_buffer := ${CFLAGS_tracepoint} -DPERF_BUFFER=1
CFLAGS_BPF_perf_buffer := ${CFLAGS_perf_buffer}

CFLAGS_map_hash := ${CFLAGS_tracepoint}
CFLAGS_BPF_map_hash := ${CFLAGS_BPF_tracepoint}
CFLAGS_map_percpu_hash := -DTRACEPOINT=1 -DMAP_PERCPU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_percpu_hash := ${CFLAGS_map_percpu_hash}
CFLAGS_map_lru_hash := -DTRACEPOINT=1 -DMAP_LRU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_lru_hash := ${CFLAGS_map_lru_hash}
CFLAGS_map_lru_percpu_hash := -DTRACEPOINT=1 -DMAP_LRU_PERCPU_HASH=1 -DSEC_DEF_TRACEPOINT=1
CFLAGS_BPF_map_lru_percpu_hash := ${CFLAGS_map_lru_percpu_hash}
CFLAGS_map_array := -DSOCKET_FILTER=1 -DRING_BUFFER=1 -DMAP_ARRAY=1
CFLAGS_BPF_map_array := ${CFLAGS_map_array}
CFLAGS_map_percpu_array := -DSOCKET_FILTER=1 -DRING_BUFFER=1 -DMAP_PERCPU_ARRAY=1
CFLAGS_BPF_map_percpu_array := ${CFLAGS_map_percpu_array}
CFLAGS_map_prog_array := -DSOCKET_FILTER=1 -DRING_BUFFER=1 -DMAP_PROG_ARRAY=1
CFLAGS_BPF_map_prog_array := ${CFLAGS_map_prog_array}
CFLAGS_BPF_map_ringbuf := -DRING_BUFFER=1 -DMAP_ARRAY=1
CFLAGS_BPF_map_devmap := ${CFLAGS_BPF_xdp_devmap}

CFLAGS_rbtree := -DTEST_RBTREE=1
CFLAGS_BPF_rbtree := ${CFLAGS_rbtree}
CFLAGS_rbtree-raw-map := ${CFLAGS_rbtree} -DTEST_RBTREE_RAW_MAP=1
CFLAGS_BPF_rbtree-raw-map := ${CFLAGS_rbtree-raw-map}

CFLAGS_spin_lock := -DTEST_SPIN_LOCK=1
CFLAGS_BPF_spin_lock := ${CFLAGS_spin_lock}

CFLAGS += $(libbpf-cflags)
CFLAGS_BPF += $(libbpf-cflags)
LDFLAGS += -Wl,-rpath,$(shell pwd)
