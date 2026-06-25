# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Helper functions are part of a stable UAPI and generally remain backward
# compatible.
#
# Kfunc (kernel functions) are internal exports of the kernel exposed to BPF,
# and there is no ABI stability guarantee, meaning they may change between
# kernel versions.
#
# Output definitions:
# - SUPPORT_<upcase helper or kfunc name>=[y]
# - bpf-helper-cflags=-DSUPPORT_<upcase helper or kfunc name>=1 ...
#
ifndef _BPF_HELPER_MK
_BPF_HELPER_MK = 1
_BPF_KFUNC_MK = 1

include dir.mk
include file.mk

# Use cache first if it's exist, because it's fast,
# see commit d48999813cd4 ("bpf/helper.mk: support cache")
cachefile := ${TOPDIR}/template/bpf/.helper.mk.cache
origfile := ${TOPDIR}/template/bpf/helper.mk
ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else

include kernel.mk
include pahole.mk
include string.mk
include bpf/btf.mk

include bits/mk-cache.mk

bpf-helper-cflags :=

# $1 - helper or kfunc name in lowercase
# $2 - helper or kfunc name in uppercase
define ___bpf_def_helper
  export SUPPORT_$(2) := y
  bpf-helper-cflags += -DSUPPORT_$(2)=1
  $(if $(DEBUG),$(info Found $(1)() and define SUPPORT_$(2)))
endef
define bpf_def_helper
  $(eval $(call ___bpf_def_helper,${1},$(call toupper_shell,${1})))
  $(call make_append_var_to_file,SUPPORT_$(call toupper_shell,${1}),${cachefile})
endef

# linux v3.18-rc4-943-gd0003ec01c66
# commit d0003ec01c66 ("bpf: allow eBPF programs to use maps")
# u64 bpf_map_lookup_elem(struct bpf_map *, void *) = 1;
$(call bpf_def_helper,bpf_map_lookup_elem)
$(call bpf_def_helper,bpf_map_update_elem)
$(call bpf_def_helper,bpf_map_delete_elem)

# linux v5.12-rc4-1654-g7b15523a989b
# commit 7b15523a989b ("bpf: Add a bpf_snprintf helper")
ifeq ($(call kver_gt,5,12,0),y)
  $(call bpf_def_helper,bpf_snprintf)
endif

# linux v5.2-rc1-220-g8b401f9ed244
# commit 8b401f9ed244 ("bpf: implement bpf_send_signal() helper")
# https://docs.ebpf.io/linux/helper-function/bpf_send_signal/
ifeq ($(call kver_gt,5,2,0),y)
  $(call bpf_def_helper,bpf_send_signal)
endif

# linux v5.5-rc4-897-g8482941f0906
# commit 8482941f0906 ("bpf: Add bpf_send_signal_thread() helper")
# https://docs.ebpf.io/linux/helper-function/bpf_send_signal_thread/
ifeq ($(call kver_gt,5,4,0),y)
  $(call bpf_def_helper,bpf_send_signal_thread)
endif

# linux v5.15-12938-ge6f2dd0f8067
# commit e6f2dd0f8067 ("bpf: Add bpf_loop helper")
ifeq ($(call kver_ge,5,16,0),y) # failed on 5.15.131
  $(call bpf_def_helper,bpf_loop)
endif

# linux v5.16-rc4-1160-gc5fb19937455
# commit c5fb19937455 ("bpf: Add bpf_strncmp helper")
ifeq ($(call kver_gt,5,16,0),y)
  $(call bpf_def_helper,bpf_strncmp)
endif

# linux v5.16-11512-g376040e47334
# commit 376040e47334 ("bpf: Add bpf_copy_from_user_task() helper")
ifeq ($(call vmlinux_has_sym_shell,btf_bpf_copy_from_user_task),y)
  $(call bpf_def_helper,bpf_copy_from_user_task)
endif

# linux v5.18-rc3-856-g263ae152e962
# commit 263ae152e962 ("bpf: Add bpf_dynptr_from_mem for local dynptrs")
# u64 bpf_dynptr_from_mem(void *, u32, u64, struct bpf_dynptr_kern *) = 197;
ifeq ($(call kver_ge,5,18,0),y)
  $(call bpf_def_helper,bpf_dynptr_from_mem)
endif

# linux v5.18-rc3-858-g13bbbfbea759
# commit 13bbbfbea759 ("bpf: Add bpf_dynptr_read and bpf_dynptr_write")
# u64 bpf_dynptr_read(void *, u32, const struct bpf_dynptr_kern *, u32, u64) = 201;
# u64 bpf_dynptr_write(const struct bpf_dynptr_kern *, u32, void *, u32, u64) = 202;
ifeq ($(call kver_ge,5,18,0),y)
  $(call bpf_def_helper,bpf_dynptr_read)
  $(call bpf_def_helper,bpf_dynptr_write)
endif

# linux v5.18-rc3-857-gbc34dee65a65
# commit bc34dee65a65 ("bpf: Dynptr support for ring buffers")
# long bpf_ringbuf_reserve_dynptr(void *ringbuf, u32 size, u64 flags, struct bpf_dynptr *ptr);
# void bpf_ringbuf_submit_dynptr(struct bpf_dynptr *ptr, u64 flags);
# void bpf_ringbuf_discard_dynptr(struct bpf_dynptr *ptr, u64 flags);
ifeq ($(call kver_ge,5,18,0),y)
  $(call bpf_def_helper,bpf_ringbuf_reserve_dynptr)
  $(call bpf_def_helper,bpf_ringbuf_submit_dynptr)
  $(call bpf_def_helper,bpf_ringbuf_discard_dynptr)
endif

# linux v6.0-11954-gc4bcfb38a95e
# commit c4bcfb38a95e ("bpf: Implement cgroup storage available to non-cgroup-attached bpf progs")
ifeq ($(call kver_ge,6,0,0),y)
  $(call bpf_def_helper,bpf_cgrp_storage_get)
endif

# linux v6.1-rc4-1163-g3f0e6f2b41d3
# commit 3f0e6f2b41d3 ("bpf: Add bpf_task_from_pid() kfunc")
ifeq ($(call kver_ge,6,1,0),y)
  $(call bpf_def_helper,bpf_task_from_pid)
endif

# linux v6.2-5289-gb5964b968ac6
# commit b5964b968ac6 ("bpf: Add skb dynptrs")
# int bpf_dynptr_from_skb(struct __sk_buff *s, u64 flags, struct bpf_dynptr *ptr__uninit);
ifeq ($(call kver_ge,6,2,0),y)
  $(call bpf_def_helper,bpf_dynptr_from_skb)
endif

# linux v6.2-5267-g332ea1f697be
# commit 332ea1f697be ("bpf: Add bpf_cgroup_from_id() kfunc")
ifeq ($(call vmlinux_has_sym_shell,bpf_cgroup_from_id),y)
  $(call bpf_def_helper,bpf_cgroup_from_id)
endif
ifeq ($(call vmlinux_has_sym_shell,bpf_cgroup_acquire),y)
  $(call bpf_def_helper,bpf_cgroup_acquire)
endif

# linux v6.2-5290-g05421aecd4ed
# commit 05421aecd4ed ("bpf: Add xdp dynptrs")
# int bpf_dynptr_from_xdp(struct xdp_md *x, u64 flags, struct bpf_dynptr *ptr__uninit);
ifeq ($(call kver_ge,6,2,0),y)
  $(call bpf_def_helper,bpf_dynptr_from_xdp)
endif

# linux v6.2-5291-g66e3a13e7c2c
# commit 66e3a13e7c2c ("bpf: Add bpf_dynptr_slice and bpf_dynptr_slice_rdwr")
# void *bpf_dynptr_slice(const struct bpf_dynptr *p, u32 offset, void *buffer__opt, u32 buffer__szk);
# void *bpf_dynptr_slice_rdwr(const struct bpf_dynptr *p, u32 offset, void *buffer__opt, u32 buffer__szk);
ifeq ($(call kver_ge,6,2,0),y)
  $(call bpf_def_helper,bpf_dynptr_slice)
  $(call bpf_def_helper,bpf_dynptr_slice_rdwr)
endif

# linux v6.6-rc2-737-g4ac454682158
# commit 4ac454682158 ("bpf: Introduce task_vma open-coded iterator kfuncs")
# see also iter in linux v5.11-rc4-606-g3a7b35b899de
# commit 3a7b35b899de ("bpf: Introduce task_vma bpf_iter")
ifeq ($(call kver_ge,6,6,0),y)
  ifeq ($(call vmlinux_has_sym_shell,bpf_iter_task_vma_new),y)
    $(call bpf_def_helper,bpf_iter_task_vma_new)
    $(call bpf_def_helper,bpf_iter_task_vma_next)
    $(call bpf_def_helper,bpf_iter_task_vma_destroy)
  endif
endif

# linux v6.10-12667-gd08e2045ebf0
# commit d08e2045ebf0 ("bpf: introduce new VFS based BPF kfuncs")
ifeq ($(call kver_gt,6,10,0),y)
  ifeq ($(call vmlinux_has_sym_shell,bpf_path_d_path),y)
    $(call bpf_def_helper,bpf_path_d_path)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_get_task_exe_file),y)
    $(call bpf_def_helper,bpf_get_task_exe_file)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_put_file),y)
    $(call bpf_def_helper,bpf_put_file)
  endif
endif

# linux v6.14-rc1-81-gf0f8a5b58f78
# commit f0f8a5b58f78 ("bpf: Add bpf_copy_from_user_task_str() kfunc")
ifeq ($(call vmlinux_has_sym_shell,bpf_copy_from_user_task_str),y)
  $(call bpf_def_helper,bpf_copy_from_user_task_str)
endif

# linux v6.15-rc4-68-g9e3e66c553f7
# commit 9e3e66c553f7 ("bpf: Add bpf_rbtree_{root,left,right} kfunc")
ifeq ($(call kver_ge,6,15,0),y)
  $(call bpf_def_helper,bpf_rbtree_root)
  $(call bpf_def_helper,bpf_rbtree_left)
  $(call bpf_def_helper,bpf_rbtree_right)
endif

# linux >= v6.15
# commit e91370550f1f ("bpf: Add kfuncs for read-only string operations") add string kfunc.
ifeq ($(call kver_gt,6,16,0),y)
  ifeq ($(call vmlinux_has_sym_shell,bpf_strcmp),y)
    $(call bpf_def_helper,bpf_strcmp)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_strlen),y)
    $(call bpf_def_helper,bpf_strlen)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_strnlen),y)
    $(call bpf_def_helper,bpf_strnlen)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_strnstr),y)
    $(call bpf_def_helper,bpf_strnstr)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_strstr),y)
    $(call bpf_def_helper,bpf_strstr)
  endif
endif

# linux v6.17-rc1-1-g89d912e494f7
# commit 89d912e494f7 ("bpf: Add dynptr type for skb metadata")
# int bpf_dynptr_from_skb_meta(struct __sk_buff *skb_, u64 flags, struct bpf_dynptr *ptr__uninit);
ifeq ($(call kver_ge,6,17,0),y)
  $(call bpf_def_helper,bpf_dynptr_from_skb_meta)
endif

# linux v6.17-rc1-99-g19559e844184
# commit 19559e844184 ("bpf: add bpf_strcasecmp kfunc")
ifeq ($(call vmlinux_has_sym_shell,bpf_strcasecmp),y)
  $(call bpf_def_helper,bpf_strcasecmp)
endif

# linux v6.17-9944-gb5b693f73589
# commit b5b693f73589 ("bpf: add bpf_strcasestr,bpf_strncasestr kfuncs")
ifeq ($(call vmlinux_has_sym_shell,bpf_strcasestr),y)
  $(call bpf_def_helper,bpf_strcasestr)
  $(call bpf_def_helper,bpf_strncasestr)
endif

# linux v6.19-rc5-205-g1dc669646762
# commit 1dc669646762 ("bpf: add bpf_strncasecmp kfunc")
ifeq ($(call kver_ge,6,19,0),y)
  $(call bpf_def_helper,bpf_strncasecmp)
endif

# See BPF_NO_KFUNC_PROTOTYPES in test-linux/bpf/libbpf/bpf_misc.h
ifeq ($(call pahole_lt,1,26),y)
  bpf-helper-cflags += -DBPF_NO_KFUNC_PROTOTYPES=1
endif

# From here, store developing kfuncs checks

# https://github.com/Rtoax/linux/tree/p056-bpf_task_cwd
# lkml: https://lore.kernel.org/lkml/tencent_97F8B56B340F51DB604B482FEBF012460505@qq.com/
ifeq ($(shell grep -wo -m1 bpf_task_cwd_from_pid /proc/kallsyms),bpf_task_cwd_from_pid)
  bpf-helper-cflags += -DSUPPORT_BPF_TASK_CWD_FROM_PID=1
endif

$(call make_append_var_to_file,bpf-helper-cflags,${cachefile})

endif # end of include cache file

export bpf-helper-cflags

ifdef DEBUG
  $(info bpf-helper-cflags = ${bpf-helper-cflags})
endif

# Do a necessary check.
ifeq ($(call kver_gt,3,18,0),y)
  ifndef SUPPORT_BPF_MAP_LOOKUP_ELEM
    $(error Not found bpf_map_lookup_elem(), some thing wrong!)
  endif
endif

endif
