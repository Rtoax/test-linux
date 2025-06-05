# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk
include ../../kernel.mk
ifndef NO_PAHOLE
  include ../../pahole/pahole.mk
endif

OUTPUT := $(abspath .output)
VIRT_TYPE ?= $(shell systemd-detect-virt)

VMLINUX_H := ${OUTPUT}/vmlinux.h

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

UID=$(shell id -u)

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
kconfig-obj-$(CONFIG_PERF_EVENTS) += perf_event
# fentry: -pg -mfentry
#  fentry + BPF trampoline ~= kprobe hook
kconfig-obj-$(CONFIG_HAVE_FENTRY) += fentry
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_bpf
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_socket_create
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_socket_sendmsg
kconfig-obj-$(CONFIG_BPF_LSM) += lsm_file_open

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
  CFLAGS_BPF += -DSUPPORT_BPF_PATH_D_PATH=1
  # bpf_get_task_exe_file()
  CFLAGS_BPF += -DSUPPORT_BPF_GET_TASK_EXE_FILE=1
  # bpf_put_file()
  CFLAGS_BPF += -DSUPPORT_BPF_PUT_FILE=1
endif

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
  $(warning "Could not support virt type ${VIRT_TYPE} in systemd-nspawn")
  TARGETS :=
  TARGETS_BPF :=
  TARGETS_SKEL :=
endif

TARGETS_BTF := btf_ksym
TARGETS_BTF += btf_kfunc
TARGETS_BTF += btf_decl_tag

# FIXME: vmlinux.h use macro 'restrict'
# TODO: linux selftests/bpf is -std=gnu11
CFLAGS_BPF += -std=gnu89 -Drestrict=
CFLAGS_BPF += -I.
CFLAGS_BPF += -O2 -Wall -g
# Like -target bpfel
CFLAGS_BPF += -target bpf -mlittle-endian
CFLAGS_BPF += -mcpu=v3
ifeq ($(CONFIG_ARCH_HAS_SYSCALL_WRAPPER),y)
  CFLAGS_BPF += -DCONFIG_ARCH_HAS_SYSCALL_WRAPPER=1
endif

CFLAGS += -lbpf
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
  $(warning "Not config CONFIG_BPF_KPROBE_OVERRIDE=y, skip test bpf_override_return()")
endif
CFLAGS_fentry := -DFENTRY=1
CFLAGS_BPF_fentry := ${CFLAGS_fentry}
CFLAGS_fmod_ret := -DFMOD_RET=1
CFLAGS_BPF_fmod_ret := ${CFLAGS_fmod_ret}
CFLAGS_socket_filter := -DSOCKET_FILTER=1 -DSTRICT_SEC_NAME=1 -DMAP_ARRAY=1
CFLAGS_BPF_socket_filter := ${CFLAGS_socket_filter}
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
CFLAGS_xdp := -DSTRICT_SEC_NAME=1 -DXDP_BASIC=1 -DXDP_BASIC_DUMMY=1 -DXDP_BASIC_TX=1 -DXDP_BASIC_PRINTK=1
CFLAGS_BPF_xdp := ${CFLAGS_xdp}
CFLAGS_xdp_devmap := -DSTRICT_SEC_NAME=1 -DXDP_DEVMAP=1
ifeq ($(call vmlinux_has_struct,bpf_devmap_val),y)
  CFLAGS_xdp_devmap += -DHAVE_STRUCT_BPF_DEVMAP_VAL=1
else
  $(warning not found struct bpf_devmap_val {})
endif
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

CFLAGS_btf_kfunc := -DTEST_BTF_KIND_FUNC=1
CFLAGS_btf_decl_tag := -DTEST_BTF_KIND_DECL_TAG=1

CFLAGS_rbtree := -DTEST_RBTREE=1
CFLAGS_BPF_rbtree := ${CFLAGS_rbtree}
CFLAGS_rbtree-raw-map := ${CFLAGS_rbtree} -DTEST_RBTREE_RAW_MAP=1
CFLAGS_BPF_rbtree-raw-map := ${CFLAGS_rbtree-raw-map}

CFLAGS_spin_lock := -DTEST_SPIN_LOCK=1
CFLAGS_BPF_spin_lock := ${CFLAGS_spin_lock}

SOCKET_HELPERS := ${OUTPUT}/socket_helpers.o
TASK_HELPERS := ${OUTPUT}/task_helpers.o
TRACE_HELPERS := ${OUTPUT}/trace_helpers.o
LIBBPF_WRAPPER := ${OUTPUT}/libbpf_wrapper.o
LIBXDP_HELPERS := ${OUTPUT}/libxdp_helpers.o
BTF_HELPERS := ${OUTPUT}/btf_helpers.o

.PHONY: build
build: libbpf_version ${VMLINUX_H} ${TARGETS_BPF} ${TARGETS_SKEL} ${TARGETS} ${TARGETS_BTF}
	${Q}./libbpf_version | sed 's/^/  /g'
	@echo -e "  \033[1;33mDone\033[m"

${OUTPUT}/socket_helpers.o: socket_helpers.h
${OUTPUT}/trace_helpers.o: trace_helpers.h
${OUTPUT}/task_helpers.o: task_helpers.h
${OUTPUT}/libbpf_wrapper.o: libbpf_wrapper.h
${OUTPUT}/libxdp_helpers.o: libxdp_helpers.h
${OUTPUT}/btf_helpers.o: btf_helpers.h

btf_ksym: ${OUTPUT}/btf_ksym.o ${BTF_HELPERS}
btf_kfunc: ${OUTPUT}/btf_kfunc.o ${BTF_HELPERS}
btf_decl_tag: ${OUTPUT}/btf_decl_tag.o ${BTF_HELPERS}
libbpf_version: ${OUTPUT}/libbpf_version.o

${OUTPUT}/config-map.o: ${OUTPUT}/config-map.skel.h config-map.h
config-map: ${OUTPUT}/config-map.o ${LIBBPF_WRAPPER}
socket_filter: ${OUTPUT}/socket_filter.o ${SOCKET_HELPERS}
tc: ${OUTPUT}/tc.o
${OUTPUT}/tc.o: ${OUTPUT}/tc.skel.h
${OUTPUT}/rbtree.o: rbtree.h ${OUTPUT}/rbtree.skel.h
${OUTPUT}/rbtree.bpf.o: rbtree.h
rbtree: ${OUTPUT}/rbtree.o ${LIBBPF_WRAPPER}
${OUTPUT}/rbtree-raw-map.o: rbtree.h
${OUTPUT}/rbtree-raw-map.bpf.o: rbtree.h
rbtree-raw-map: ${OUTPUT}/rbtree-raw-map.o ${LIBBPF_WRAPPER}
${OUTPUT}/spin_lock.o: spin_lock.h
${OUTPUT}/spin_lock.bpf.o: spin_lock.h
spin_lock: ${OUTPUT}/spin_lock.o ${LIBBPF_WRAPPER}
xdp: ${OUTPUT}/xdp.o ${LIBBPF_WRAPPER}
xdp_simple: ${OUTPUT}/xdp_simple.o ${LIBBPF_WRAPPER} ${LIBXDP_HELPERS}
xdp_dos: ${OUTPUT}/xdp_dos.o ${LIBBPF_WRAPPER} ${LIBXDP_HELPERS}
xdp_devmap: ${OUTPUT}/xdp_devmap.o ${LIBBPF_WRAPPER}
xdp_cpumap: ${OUTPUT}/xdp_cpumap.o ${LIBBPF_WRAPPER}
xdp_xskmap: ${OUTPUT}/xdp_xskmap.o ${LIBBPF_WRAPPER} ${LIBXDP_HELPERS}
sockops: ${OUTPUT}/sockops.o
kprobe: ${OUTPUT}/kprobe.o
tracepoint: ${OUTPUT}/tracepoint.o ${LIBBPF_WRAPPER}
${OUTPUT}/tracepoint.bpf.o: tracepoint.h bpf_helpers.h
raw_tracepoint: ${OUTPUT}/raw_tracepoint.o ${LIBBPF_WRAPPER}
tp_btf: ${OUTPUT}/tp_btf.o ${LIBBPF_WRAPPER}
perf_event: ${OUTPUT}/perf_event.o
sk_skb: ${OUTPUT}/sk_skb.o
sk_msg: ${OUTPUT}/sk_msg.o
cgroup_device: ${OUTPUT}/cgroup_device.o
cgroup_sysctl: ${OUTPUT}/cgroup_sysctl.o
fentry: ${OUTPUT}/fentry.o
fmod_ret: ${OUTPUT}/fmod_ret.o
iter_task: ${OUTPUT}/iter_task.o ${TASK_HELPERS}
iter_task_file: ${OUTPUT}/iter_task_file.o
iter_task_vma: ${OUTPUT}/iter_task_vma.o
iter_bpf_map: ${OUTPUT}/iter_bpf_map.o
iter_kmem_cache: ${OUTPUT}/iter_kmem_cache.o
lsm_bpf: ${OUTPUT}/lsm_bpf.o
${OUTPUT}/lsm_bpf.bpf.o: bpf_helpers.h
lsm_socket_create: ${OUTPUT}/lsm_socket_create.o
${OUTPUT}/lsm_socket_create.bpf.o: bpf_helpers.h
lsm_socket_sendmsg: ${OUTPUT}/lsm_socket_sendmsg.o
${OUTPUT}/lsm_socket_sendmsg.bpf.o: bpf_helpers.h

map_hash: ${OUTPUT}/map_hash.o ${LIBBPF_WRAPPER}
map_percpu_hash: ${OUTPUT}/map_percpu_hash.o ${LIBBPF_WRAPPER}
map_lru_hash: ${OUTPUT}/map_lru_hash.o ${LIBBPF_WRAPPER}
map_lru_percpu_hash: ${OUTPUT}/map_lru_percpu_hash.o ${LIBBPF_WRAPPER}
map_array: ${OUTPUT}/map_array.o ${SOCKET_HELPERS}
map_percpu_array: ${OUTPUT}/map_percpu_array.o ${SOCKET_HELPERS}

${OUTPUT}:
	@echo -e "  MKDIR  \033[1m${@}\033[m"
	${Q}mkdir -p $(@)

${OUTPUT}/%.bpf.o: %.bpf.c ${VMLINUX_H} | ${OUTPUT} libbpf_version
	@echo -e "  BPF  \033[1m$(notdir ${@})\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*)) $(CLANG_V) $(shell ./libbpf_version cflags)
	${Q}${PAHOLE} $(@) > $(@:.bpf.o=.btf.h) || rm $(@:.bpf.o=.btf.h)

${OUTPUT}/%.skel.h: ${OUTPUT}/%.bpf.o | ${OUTPUT}
	@echo -e "  SKEL  \033[1m$(notdir ${@})\033[m"
	${Q}$(BPFTOOL) gen object $(<:.o=.linked1.o) $(<)
	${Q}$(BPFTOOL) gen object $(<:.o=.linked2.o) $(<:.o=.linked1.o)
	${Q}$(BPFTOOL) gen object $(<:.o=.linked3.o) $(<:.o=.linked2.o)
	${Q}diff $(<:.o=.linked2.o) $(<:.o=.linked3.o)
	${Q}$(BPFTOOL) gen skeleton $(SKEL_ARGS) $(SKEL_ARGS_$(*)) \
		$(<:.o=.linked3.o) name $(subst -,_,$(notdir $(<:.bpf.o=)))_bpf > $@ || rm -f $@
	# FIXME: old bpftool not support 'gen subskeleton' command.
	# bpftool commit ad805235e295 ("bpftool: Add support for subskeletons")
	# https://github.com/libbpf/bpftool.git
	#${Q}$(BPFTOOL) gen subskeleton \
	#	$(<:.o=.linked3.o) name $(subst -,_,$(notdir $(<:.bpf.o=)))_bpf > $(@:.skel.h=.subskel.h)

${OUTPUT}/%.o: %.c ${OUTPUT}/%.skel.h | ${OUTPUT}
	@echo -e "  CC  \033[1m$(notdir ${@})\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}/%.o: %.c | ${OUTPUT}
	@echo -e "  CC(LIB)  \033[1m$(notdir ${@})\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS) libbpf_version ${TARGETS_BTF}: %: ${OUTPUT}/%.o ${TRACE_HELPERS}
	@echo -e "  LD  \033[1;32m$(notdir ${@})\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

include ../bpftool/vmlinux.h.mk

.PHONY: clean
clean:
	@echo -e "  RM  \033[1;32m$(TARGETS_BPF) ${TARGETS}\033[m"
	${Q}rm -f ${TARGETS_BPF} ${TARGETS} *.o ${VMLINUX_H} libbpf_version
	${Q}rm -rf ${OUTPUT} ${TARGETS_BTF}
