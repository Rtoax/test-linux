# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - SUPPORT_$(kfunc)=[y]
# - bpf-helper-cflags=
#
_BPF_HELPER = 1
_BPF_KFUNC = 1

include kernel.mk
include string.mk
include bpf/btf.mk

bpf-helper-cflags :=

# $1 - helper or kfunc name in lowercase
define ___define_helper
  export SUPPORT_$(call toupper_shell,$(1)) := y
  bpf-helper-cflags += -DSUPPORT_$(call toupper_shell,$(1))=1
  $(info Found ${1}())
endef
define define_helper
  $(eval $(call ___define_helper,${1}))
endef

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

export bpf-helper-cflags

ifdef DEBUG
  $(info bpf-helper-cflags = ${bpf-helper-cflags})
endif
