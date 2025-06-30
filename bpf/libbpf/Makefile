# SPDX-License-Identifier: GPL-3.0
include ../../kernel.mk
ifndef NO_PAHOLE
  include ../../pahole/pahole.mk
endif

OUTPUT := .output/
VMLINUX_H := ${OUTPUT}vmlinux.h

include ../../kconfig.mk
include ../bpf.mk
include ../../glibc/ldconfig.mk
include ./libbpf.mk
include ../btf/btf.mk
include ../bpftool/bpftool.mk

KSYM_DO_EXECVEAT_COMMON := $(shell grep 't do_execveat_common' /proc/kallsyms \
			| head -1 \
			| awk '{print $$3}')

ifdef DEBUG
  $(info KSYM_DO_EXECVEAT_COMMON = ${KSYM_DO_EXECVEAT_COMMON})
endif

UID := $(shell id -u)

CC := gcc
CLANG := clang

CFLAGS :=
CFLAGS_BPF :=
# bpftool gen skeleton
SKEL_ARGS :=

kconfig-obj-y :=
kconfig-obj-$(CONFIG_KPROBES) += kprobe
kconfig-obj-$(CONFIG_TRACEPOINTS) += tracepoint raw_tracepoint tp_btf
kconfig-obj-$(CONFIG_TRACEPOINTS) += map_hash map_lru_hash map_percpu_hash map_lru_percpu_hash
kconfig-obj-$(CONFIG_PERF_EVENTS) += perf_event perf_buffer
# fentry: -pg -mfentry
#  fentry + BPF trampoline ~= kprobe hook
kconfig-obj-$(CONFIG_HAVE_FENTRY) += fentry
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_bpf
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_socket_create
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_socket_sendmsg
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_file_open
kconfig-obj-$(CONFIG_RING_BUFFER) += ring_buffer

ifdef DEBUG
  $(info kconfig-obj-y : $(kconfig-obj-y))
  $(info kconfig-obj-n : $(kconfig-obj-))
endif

TARGETS :=
TARGETS += config-map
TARGETS += socket_filter
TARGETS += tc
TARGETS += xdp xdp_simple xdp_dos
# kernel v4.12-11037-g546ac1ffb70d
# commit 546ac1ffb70d ("bpf: add devmap, a map for storing net device references")
ifeq ($(call kernel_newer_than,4,12,0),y)
  TARGETS += xdp_devmap
endif
# kernel v5.8-rc4-1449-g9216477449f3
# commit 9216477449f3 ("bpf: cpumap: Add the possibility to attach an eBPF program to cpumap")
# struct bpf_cpumap_val support bpf_prog field
# kernel v5.8-rc4-1448-g644bfe51fa49
# commit 644bfe51fa49 ("cpumap: Formalize map value as a named struct")
# introduce struct bpf_cpumap_val
ifeq ($(call kernel_newer_than,5,8,0),y)
  TARGETS += xdp_cpumap
endif

# linux commit e6f2dd0f8067 ("bpf: Add bpf_loop helper")
# v5.15-12938-ge6f2dd0f8067
ifeq ($(call kernel_newer_than,5,15,0),y)
  CFLAGS_BPF += -DSUPPORT_BPF_LOOP=1
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
ifeq ($(call kernel_newer_than,6,12,0),y)
  # linux v6.12-rc1-177-g4971266e1595
  # commit 4971266e1595 ("bpf: Add kmem_cache iterator")
  TARGETS += iter_kmem_cache
endif
TARGETS += $(kconfig-obj-y)
TARGETS += map_array map_percpu_array
TARGETS += xdp_xskmap

# linux commit bd1279ae8a69 ("bpf: Add bpf_rbtree_{add,remove,first} kfuncs")
# v6.2-rc7-1572-gbd1279ae8a69
ifeq ($(call kernel_newer_than,6,2,0),y)
  # linux commit 9c395c1b99bd ("bpf: Add basic bpf_rb_{root,node} support")
  # v6.2-rc7-1571-g9c395c1b99bd add bpf_rb_root to uapi/linux/bpf.h
  ifeq ($(call kuapi_lower_than,6,2,0),y)
    $(warning "kuapi not support bpf_rb_root")
    CFLAGS += -DKAPI_NO_BPF_RB_ROOT=1
  endif
  TARGETS += rbtree
  TARGETS += rbtree-raw-map
  # linux commit 9e3e66c553f7 ("bpf: Add bpf_rbtree_{root,left,right} kfunc")
  # v6.15-rc4-68-g9e3e66c553f7
  ifeq ($(call kernel_newer_than,6,14,0),y)
    CFLAGS_BPF += -DSUPPORT_BPF_RBTREE_ROOT=1
    CFLAGS_BPF += -DSUPPORT_BPF_RBTREE_LEFT=1
    CFLAGS_BPF += -DSUPPORT_BPF_RBTREE_RIGHT=1
  endif
endif

# linux commit d83525ca62cf ("bpf: introduce bpf_spin_lock")
# v5.0-rc4-620-gd83525ca62cf
ifeq ($(call kernel_newer_than,5,0,0),y)
  TARGETS += spin_lock
endif

# linux commit 7b15523a989b ("bpf: Add a bpf_snprintf helper")
# v5.12-rc4-1654-g7b15523a989b
ifeq ($(call kernel_newer_than,5,12,0),y)
  CFLAGS_BPF += -DSUPPORT_BPF_SNPRINTF=1
endif
# linux commit c5fb19937455 ("bpf: Add bpf_strncmp helper")
# v5.16-rc4-1160-gc5fb19937455
ifeq ($(call kernel_newer_than,5,16,0),y)
  CFLAGS_BPF += -DSUPPORT_BPF_STRNCMP=1
endif
# linux commit d08e2045ebf0 ("bpf: introduce new VFS based BPF kfuncs")
# v6.10-12667-gd08e2045ebf0
ifeq ($(call kernel_newer_than,6,10,0),y)
  # bpf_path_d_path()
  ifeq ($(call vmlinux_has_sym,bpf_path_d_path),y)
    CFLAGS_BPF += -DSUPPORT_BPF_PATH_D_PATH=1
  endif
  # bpf_get_task_exe_file()
  ifeq ($(call vmlinux_has_sym,bpf_get_task_exe_file),y)
    CFLAGS_BPF += -DSUPPORT_BPF_GET_TASK_EXE_FILE=1
  endif
  # bpf_put_file()
  ifeq ($(call vmlinux_has_sym,bpf_put_file),y)
    CFLAGS_BPF += -DSUPPORT_BPF_PUT_FILE=1
  endif
endif

# _if_ there are no user mode code, append to bpf target only
obj-bpf.o := ${TARGETS:=.bpf.o}
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
obj-bpf.o += map_array_of_maps.bpf.o
obj-bpf.o += map_hash_of_maps.bpf.o
obj-bpf.o += map_ringbuf.bpf.o
obj-bpf.o += map_devmap.bpf.o
obj-bpf.o += map_arena.bpf.o
obj-bpf.o += map_bloom_filter.bpf.o
obj-bpf.o += sched_cls.bpf.o
obj-bpf.o += sched_act.bpf.o

TARGETS_BPF := $(addprefix ${OUTPUT},${obj-bpf.o})

TARGETS_BTF := btf_ksym
TARGETS_BTF += btf_kfunc
TARGETS_BTF += btf_decl_tag

# FIXME: vmlinux.h use macro 'restrict'
# TODO: linux selftests/bpf is -std=gnu11
CFLAGS_BPF += -std=gnu89 -Drestrict=
CFLAGS_BPF += -I.
CFLAGS_BPF += -O2 -g
# Like -target bpfel
CFLAGS_BPF += -target bpf -mlittle-endian
CFLAGS_BPF += -mcpu=v3
ifeq ($(CONFIG_ARCH_HAS_SYSCALL_WRAPPER),y)
  CFLAGS_BPF += -DCONFIG_ARCH_HAS_SYSCALL_WRAPPER=1
endif

CFLAGS += -lbpf
CFLAGS += -O0 -g
LDFLAGS := -lbpf
LDFLAGS += -O0 -g
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

CFLAGS_PAHOLE := -DPAHOLE_VERSION_MAJOR=${PAHOLE_VERSION_MAJOR}
CFLAGS_PAHOLE += -DPAHOLE_VERSION_MINOR=${PAHOLE_VERSION_MINOR}

CFLAGS += ${CFLAGS_PAHOLE}
CFLAGS_BPF += ${CFLAGS_PAHOLE}

ifneq ($(call vmlinux_has_sym,bpf_task_from_pid),y)
  # FIXME: some day use CFLAGS_PAHOLE replace this macro
  CFLAGS_BPF += -DBPF_NO_KFUNC_PROTOTYPES=1
endif

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
# https://github.com/Rtoax/linux/tree/p056-bpf_task_cwd
ifeq ($(shell grep -wo bpf_task_cwd_from_pid /proc/kallsyms),bpf_task_cwd_from_pid)
  CFLAGS_tracepoint += -DSUPPORT_BPF_TASK_CWD_FROM_PID=1
endif
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
ifeq ($(call vmlinux_has_struct,bpf_devmap_val),y)
  CFLAGS_xdp_devmap += -DHAVE_STRUCT_BPF_DEVMAP_VAL=1
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
CFLAGS_map_array_of_maps := -DMAP_ARRAY_OF_MAPS=1
CFLAGS_BPF_map_array_of_maps := ${CFLAGS_map_array_of_maps}
CFLAGS_map_hash_of_maps := -DMAP_HASH_OF_MAPS=1
CFLAGS_BPF_map_hash_of_maps := ${CFLAGS_map_hash_of_maps}
CFLAGS_BPF_map_ringbuf := -DRING_BUFFER=1 -DMAP_ARRAY=1
CFLAGS_BPF_map_devmap := ${CFLAGS_BPF_xdp_devmap}

CFLAGS_btf_kfunc := -DTEST_BTF_KIND_FUNC=1
CFLAGS_btf_decl_tag := -DTEST_BTF_KIND_DECL_TAG=1

CFLAGS_rbtree := -DTEST_RBTREE=1
CFLAGS_BPF_rbtree := ${CFLAGS_rbtree}
CFLAGS_rbtree-raw-map := ${CFLAGS_rbtree} -DTEST_RBTREE_RAW_MAP=1
CFLAGS_BPF_rbtree-raw-map := ${CFLAGS_rbtree-raw-map}

CFLAGS_spin_lock := -DTEST_SPIN_LOCK=1
CFLAGS_BPF_spin_lock := ${CFLAGS_spin_lock}

# Get libbpf cflags
libbpf-cflags := $(shell ${CC} libbpf_version.c ${CFLAGS} ${LDFLAGS} -o libbpf_version && \
	./libbpf_version cflags)

CFLAGS += $(libbpf-cflags)
CFLAGS_BPF += $(libbpf-cflags)

SOCKET_HELPERS := ${OUTPUT}socket_helpers.o
TASK_HELPERS := ${OUTPUT}task_helpers.o
TRACE_HELPERS := ${OUTPUT}trace_helpers.o
LIBBPF_WRAPPER := ${OUTPUT}libbpf_wrapper.o
LIBXDP_HELPERS := ${OUTPUT}libxdp_helpers.o
BTF_HELPERS := ${OUTPUT}btf_helpers.o

HELPERS := ${BTF_HELPERS} ${LIBXDP_HELPERS} ${TRACE_HELPERS} \
	   ${TASK_HELPERS} ${SOCKET_HELPERS} ${LIBBPF_WRAPPER}

TARGETS += libbpf_version
TARGETS_PREP += libbpf_version
TARGETS_PREP += test-libbpf_version
TARGETS_PREP += ${HELPERS}

include ../../template/main.mk

test-libbpf_version: libbpf_version
	${Q}./libbpf_version cflags >/dev/null
	${Q}./libbpf_version env >/dev/null
	${Q}./libbpf_version >/dev/null

${OUTPUT}socket_helpers.o: socket_helpers.h
${OUTPUT}trace_helpers.o: trace_helpers.h
${OUTPUT}task_helpers.o: task_helpers.h
${OUTPUT}libbpf_wrapper.o: libbpf_wrapper.h
${OUTPUT}libxdp_helpers.o: libxdp_helpers.h
${OUTPUT}btf_helpers.o: btf_helpers.h

btf_ksym: ${OUTPUT}btf_ksym.o ${HELPERS}
btf_kfunc: ${OUTPUT}btf_kfunc.o ${HELPERS}
btf_decl_tag: ${OUTPUT}btf_decl_tag.o ${HELPERS}
libbpf_version: ${OUTPUT}libbpf_version.o ${HELPERS}

${OUTPUT}config-map.o: ${OUTPUT}config-map.skel.h config-map.h
config-map: ${OUTPUT}config-map.o ${HELPERS}
socket_filter: ${OUTPUT}socket_filter.o ${HELPERS}
${OUTPUT}socket_filter.o: ${OUTPUT}map_array.skel.h
ring_buffer: ${OUTPUT}ring_buffer.o ${HELPERS}
tc: ${OUTPUT}tc.o ${HELPERS}
${OUTPUT}tc.o: ${OUTPUT}tc.skel.h
${OUTPUT}rbtree.o: rbtree.h ${OUTPUT}rbtree.skel.h
${OUTPUT}rbtree.bpf.o: rbtree.h
rbtree: ${OUTPUT}rbtree.o ${HELPERS}
${OUTPUT}rbtree-raw-map.o: rbtree.h
${OUTPUT}rbtree-raw-map.bpf.o: rbtree.h
rbtree-raw-map: ${OUTPUT}rbtree-raw-map.o ${HELPERS}
${OUTPUT}rbtree-raw-map.o: ${OUTPUT}rbtree-raw-map.skel.h
${OUTPUT}spin_lock.o: spin_lock.h
${OUTPUT}spin_lock.bpf.o: spin_lock.h
spin_lock: ${OUTPUT}spin_lock.o ${HELPERS}
${OUTPUT}spin_lock.o: ${OUTPUT}spin_lock.skel.h
xdp: ${OUTPUT}xdp.o ${HELPERS}
${OUTPUT}xdp.o: ${OUTPUT}xdp.skel.h
xdp_simple: ${OUTPUT}xdp_simple.o ${HELPERS}
${OUTPUT}xdp_simple.o: ${OUTPUT}xdp_simple.skel.h
xdp_dos: ${OUTPUT}xdp_dos.o ${HELPERS}
${OUTPUT}xdp_dos.o: ${OUTPUT}xdp_dos.skel.h
xdp_devmap: ${OUTPUT}xdp_devmap.o ${HELPERS}
${OUTPUT}xdp_devmap.o: ${OUTPUT}xdp_devmap.skel.h
xdp_cpumap: ${OUTPUT}xdp_cpumap.o ${HELPERS}
${OUTPUT}xdp_cpumap.o: ${OUTPUT}xdp_cpumap.skel.h
xdp_xskmap: ${OUTPUT}xdp_xskmap.o ${HELPERS}
${OUTPUT}xdp_xskmap.o: ${OUTPUT}xdp_xskmap.skel.h
sockops: ${OUTPUT}sockops.o ${HELPERS}
${OUTPUT}sockops.o: ${OUTPUT}sockops.skel.h
kprobe: ${OUTPUT}kprobe.o ${HELPERS}
${OUTPUT}kprobe.o: ${OUTPUT}kprobe.skel.h
tracepoint: ${OUTPUT}tracepoint.o ${HELPERS}
${OUTPUT}tracepoint.o: ${OUTPUT}tracepoint.skel.h ${OUTPUT}map_hash.skel.h
${OUTPUT}tracepoint.bpf.o: tracepoint.h bpf_helpers.h
raw_tracepoint: ${OUTPUT}raw_tracepoint.o ${HELPERS}
${OUTPUT}raw_tracepoint.o: ${OUTPUT}raw_tracepoint.skel.h
tp_btf: ${OUTPUT}tp_btf.o ${HELPERS}
${OUTPUT}tp_btf.o: ${OUTPUT}tp_btf.skel.h
perf_event: ${OUTPUT}perf_event.o ${HELPERS}
${OUTPUT}perf_event.o: ${OUTPUT}perf_event.skel.h
perf_buffer: ${OUTPUT}perf_buffer.o ${HELPERS}
${OUTPUT}perf_buffer.o: ${OUTPUT}perf_buffer.skel.h
sk_skb: ${OUTPUT}sk_skb.o ${HELPERS}
${OUTPUT}sk_skb.o: ${OUTPUT}sk_skb.skel.h
sk_msg: ${OUTPUT}sk_msg.o ${HELPERS}
${OUTPUT}sk_msg.o: ${OUTPUT}sk_msg.skel.h
cgroup_device: ${OUTPUT}cgroup_device.o ${HELPERS}
${OUTPUT}cgroup_device.o: ${OUTPUT}cgroup_device.skel.h
cgroup_sysctl: ${OUTPUT}cgroup_sysctl.o ${HELPERS}
${OUTPUT}cgroup_sysctl.o: ${OUTPUT}cgroup_sysctl.skel.h
fentry: ${OUTPUT}fentry.o ${HELPERS}
${OUTPUT}fentry.o: ${OUTPUT}fentry.skel.h
fmod_ret: ${OUTPUT}fmod_ret.o ${HELPERS}
${OUTPUT}fmod_ret.o: ${OUTPUT}fmod_ret.skel.h
iter_task: ${OUTPUT}iter_task.o ${HELPERS}
${OUTPUT}iter_task.o: ${OUTPUT}iter_task.skel.h
iter_task_file: ${OUTPUT}iter_task_file.o ${HELPERS}
${OUTPUT}iter_task_file.o: ${OUTPUT}iter_task_file.skel.h
iter_task_vma: ${OUTPUT}iter_task_vma.o ${HELPERS}
${OUTPUT}iter_task_vma.o: ${OUTPUT}iter_task_vma.skel.h
iter_bpf_map: ${OUTPUT}iter_bpf_map.o ${HELPERS}
${OUTPUT}iter_bpf_map.o: ${OUTPUT}iter_bpf_map.skel.h
iter_kmem_cache: ${OUTPUT}iter_kmem_cache.o ${HELPERS}
${OUTPUT}iter_kmem_cache.o: ${OUTPUT}iter_kmem_cache.skel.h
lsm_bpf: ${OUTPUT}lsm_bpf.o ${HELPERS}
${OUTPUT}lsm_bpf.o: ${OUTPUT}lsm_bpf.skel.h
${OUTPUT}lsm_file_open.bpf.o: lsm_file_open.bpf.c
${OUTPUT}lsm_file_open.o: ${OUTPUT}lsm_file_open.skel.h
${OUTPUT}lsm_file_open.skel.h: ${OUTPUT}lsm_file_open.bpf.o
lsm_file_open: ${OUTPUT}lsm_file_open.o ${HELPERS}
${OUTPUT}lsm_bpf.bpf.o: bpf_helpers.h
lsm_socket_create: ${OUTPUT}lsm_socket_create.o ${HELPERS}
${OUTPUT}lsm_socket_create.o: ${OUTPUT}lsm_socket_create.skel.h
${OUTPUT}lsm_socket_create.bpf.o: bpf_helpers.h
lsm_socket_sendmsg: ${OUTPUT}lsm_socket_sendmsg.o ${HELPERS}
${OUTPUT}lsm_socket_sendmsg.o: ${OUTPUT}lsm_socket_sendmsg.skel.h
${OUTPUT}lsm_socket_sendmsg.bpf.o: bpf_helpers.h
map_hash: ${OUTPUT}map_hash.o ${HELPERS}
${OUTPUT}map_hash.o: ${OUTPUT}map_hash.skel.h
map_percpu_hash: ${OUTPUT}map_percpu_hash.o ${HELPERS}
${OUTPUT}map_percpu_hash.o: ${OUTPUT}map_percpu_hash.skel.h
map_lru_hash: ${OUTPUT}map_lru_hash.o ${HELPERS}
map_lru_percpu_hash: ${OUTPUT}map_lru_percpu_hash.o ${HELPERS}
map_array: ${OUTPUT}map_array.o ${HELPERS}
map_percpu_array: ${OUTPUT}map_percpu_array.o ${HELPERS}
${OUTPUT}map_percpu_array.o: ${OUTPUT}map_percpu_array.skel.h

include ../bpftool/vmlinux.h.mk
