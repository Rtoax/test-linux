# SPDX-License-Identifier: GPL-3.0
#
# Helper functions are part of a stable UAPI and generally remain backward
# compatible.
#
# Kfunc (kernel functions) are internal exports of the kernel exposed to BPF,
# and there is no ABI stability guarantee, meaning they may change between
# kernel versions.
#
# Output definitions:
# - SUPPORT_$(upcase kfunc name)=[y]
# - bpf-helper-cflags=
#
ifndef _BPF_HELPER_MK
_BPF_HELPER_MK = 1
_BPF_KFUNC_MK = 1

include kernel.mk
include pahole.mk
include string.mk
include bpf/btf.mk

bpf-helper-cflags :=

# $1 - helper or kfunc name in lowercase
define ___define_helper
  HELPER_DEF := SUPPORT_$(call toupper_shell,$(1))
  export $${HELPER_DEF} := y
  bpf-helper-cflags += -DSUPPORT_$${HELPER_DEF}=1
  $(info Found ${1}() and define ${HELPER_DEF})
endef
define define_helper
  $(eval $(call ___define_helper,${1}))
endef

# linux v3.18-rc4-943-gd0003ec01c66
# commit d0003ec01c66 ("bpf: allow eBPF programs to use maps")
# u64 bpf_map_lookup_elem(struct bpf_map *, void *) = 1;
$(call define_helper,bpf_map_lookup_elem)
$(call define_helper,bpf_map_update_elem)
$(call define_helper,bpf_map_delete_elem)

# linux v5.16-rc4-1160-gc5fb19937455 commit c5fb19937455 ("bpf: Add bpf_strncmp helper")
ifeq ($(call kver_gt,5,16,0),y)
  $(call define_helper,bpf_strncmp)
endif

# linux v6.0-11954-gc4bcfb38a95e commit c4bcfb38a95e ("bpf: Implement cgroup storage available to non-cgroup-attached bpf progs")
ifeq ($(call kver_ge,6,0,0),y)
  $(call define_helper,bpf_cgrp_storage_get)
endif

# linux v5.15-12938-ge6f2dd0f8067 commit e6f2dd0f8067 ("bpf: Add bpf_loop helper")
ifeq ($(call kver_ge,5,16,0),y) # failed on 5.15.131
  $(call define_helper,bpf_loop)
endif

# linux v6.2-5267-g332ea1f697be commit 332ea1f697be ("bpf: Add bpf_cgroup_from_id() kfunc")
ifeq ($(call vmlinux_has_sym_shell,bpf_cgroup_from_id),y)
  $(call define_helper,bpf_cgroup_from_id)
endif
ifeq ($(call vmlinux_has_sym_shell,bpf_cgroup_acquire),y)
  $(call define_helper,bpf_cgroup_acquire)
endif

# linux v6.15-rc4-68-g9e3e66c553f7 commit 9e3e66c553f7 ("bpf: Add bpf_rbtree_{root,left,right} kfunc")
ifeq ($(call kver_ge,6,15,0),y)
  $(call define_helper,bpf_rbtree_root)
  $(call define_helper,bpf_rbtree_left)
  $(call define_helper,bpf_rbtree_right)
endif

# linux v5.12-rc4-1654-g7b15523a989b commit 7b15523a989b ("bpf: Add a bpf_snprintf helper")
ifeq ($(call kver_gt,5,12,0),y)
  $(call define_helper,bpf_snprintf)
endif

ifeq ($(call vmlinux_has_sym_shell,bpf_strcmp),y)
  $(call define_helper,bpf_strcmp)
endif

ifeq ($(call vmlinux_has_sym_shell,bpf_strcasecmp),y)
  $(call define_helper,bpf_strcasecmp)
endif

# NOTE: I'm working on bpf_strcasestr() and bpf_strncasestr()
ifeq ($(call vmlinux_has_sym_shell,bpf_strcasestr),y)
  $(call define_helper,bpf_strcasestr)
  $(call define_helper,bpf_strncasestr)
endif

ifeq ($(call vmlinux_has_sym_shell,bpf_strnlen),y)
  $(call define_helper,bpf_strnlen)
endif

# linux >= v6.15 commit e91370550f1f ("bpf: Add kfuncs for read-only string
# operations") add string kfunc.
ifeq ($(call kver_gt,6,16,0),y)
  ifeq ($(call vmlinux_has_sym_shell,bpf_strnstr),y)
    $(call define_helper,bpf_strnstr)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_strstr),y)
    $(call define_helper,bpf_strstr)
  endif
endif

# linux v6.10-12667-gd08e2045ebf0 commit d08e2045ebf0 ("bpf: introduce new VFS based BPF kfuncs")
ifeq ($(call kver_gt,6,10,0),y)
  ifeq ($(call vmlinux_has_sym_shell,bpf_path_d_path),y)
    $(call define_helper,bpf_path_d_path)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_get_task_exe_file),y)
    $(call define_helper,bpf_get_task_exe_file)
  endif
  ifeq ($(call vmlinux_has_sym_shell,bpf_put_file),y)
    $(call define_helper,bpf_put_file)
  endif
endif

# linux v6.6-rc2-737-g4ac454682158 commit 4ac454682158 ("bpf: Introduce task_vma open-coded iterator kfuncs")
ifeq ($(call kver_ge,6,6,0),y)
  ifeq ($(call vmlinux_has_sym_shell,bpf_iter_task_vma_new),y)
    $(call define_helper,bpf_iter_task_vma_new)
    $(call define_helper,bpf_iter_task_vma_next)
    $(call define_helper,bpf_iter_task_vma_destroy)
  endif
endif

# linux v5.16-11512-g376040e47334 commit 376040e47334 ("bpf: Add bpf_copy_from_user_task() helper")
ifeq ($(call vmlinux_has_sym_shell,btf_bpf_copy_from_user_task),y)
  $(call define_helper,bpf_copy_from_user_task)
endif

# linux v6.14-rc1-81-gf0f8a5b58f78 commit f0f8a5b58f78 ("bpf: Add bpf_copy_from_user_task_str() kfunc")
ifeq ($(call vmlinux_has_sym_shell,bpf_copy_from_user_task_str),y)
  $(call define_helper,bpf_copy_from_user_task_str)
endif

ifeq ($(call vmlinux_has_sym_shell,bpf_task_from_pid),y)
  $(call define_helper,bpf_task_from_pid)
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

# linux v5.18-rc3-856-g263ae152e962
# commit 263ae152e962 ("bpf: Add bpf_dynptr_from_mem for local dynptrs")
# u64 bpf_dynptr_from_mem(void *, u32, u64, struct bpf_dynptr_kern *) = 197;
ifeq ($(call kver_ge,5,18,0),y)
  $(call define_helper,bpf_dynptr_from_mem)
endif

# linux v5.18-rc3-858-g13bbbfbea759
# commit 13bbbfbea759 ("bpf: Add bpf_dynptr_read and bpf_dynptr_write")
# u64 bpf_dynptr_read(void *, u32, const struct bpf_dynptr_kern *, u32, u64) = 201;
# u64 bpf_dynptr_write(const struct bpf_dynptr_kern *, u32, void *, u32, u64) = 202;
ifeq ($(call kver_ge,5,18,0),y)
  $(call define_helper,bpf_dynptr_read)
  $(call define_helper,bpf_dynptr_write)
endif

# linux v6.2-5289-gb5964b968ac6
# commit b5964b968ac6 ("bpf: Add skb dynptrs")
# int bpf_dynptr_from_skb(struct __sk_buff *s, u64 flags, struct bpf_dynptr *ptr__uninit);
ifeq ($(call kver_ge,6,2,0),y)
  $(call define_helper,bpf_dynptr_from_skb)
endif

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
