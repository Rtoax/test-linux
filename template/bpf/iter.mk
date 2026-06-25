# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - SUPPORT_${<iter name>}=[y]
# - bpf-iter-cflags=-DSUPPORT_X=1
#
ifndef _BPF_ITER_MK
_BPF_ITER_MK = 1

include dir.mk
include kernel.mk
include string.mk
include bpf/btf.mk
include file.mk

# Use cache first if it's exist, because it's fast,
cachefile := ${TOPDIR}/template/bpf/.iter.mk.cache
origfile := ${TOPDIR}/template/bpf/iter.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else

include bits/mk-cache.mk

# $1 - iter name in lowercase
# $2 - iter name in uppercase
define ___bpf_def_iter
  export SUPPORT_$(2) := y
  bpf-iter-cflags += -DSUPPORT_$(2)=1
  $(if $(DEBUG),$(info Support $(1) and define SUPPORT_$(2)))
endef
define bpf_def_iter
  $(eval $(call ___bpf_def_iter,${1},$(call toupper_shell,${1})))
  $(call make_append_var_to_file,SUPPORT_$(call toupper_shell,${1}),${cachefile})
endef

# linux v5.7-rc2-1178-g6086d29def80
# commit 6086d29def80 ("bpf: Add bpf_map iterator")
ifeq ($(call kver_ge,5,7,0),y)
  $(call bpf_def_iter,iter_bpf_map)
endif

# linux v5.7-rc2-1180-geaaacd23910f
# commit eaaacd23910f ("bpf: Add task and task/file iterator targets")
ifeq ($(call kver_ge,5,7,0),y)
  $(call bpf_def_iter,iter_task)
  $(call bpf_def_iter,iter_task_file)
endif

# linux v5.11-rc4-606-g3a7b35b899de
# commit 3a7b35b899de ("bpf: Introduce task_vma bpf_iter")
# see also kfuncs in linux v6.6-rc2-737-g4ac454682158
# commit 4ac454682158 ("bpf: Introduce task_vma open-coded iterator kfuncs")
ifeq ($(call kver_ge,5,7,0),y)
  $(call bpf_def_iter,iter_task_vma)
endif

# linux v6.12-rc1-177-g4971266e1595
# commit 4971266e1595 ("bpf: Add kmem_cache iterator")
# - debian13 6.12.73+deb13-amd64 not support
ifeq ($(call kver_gt,6,12,73),y)
  $(call bpf_def_iter,iter_kmem_cache)
endif

$(call make_append_var_to_file,bpf-iter-cflags,${cachefile})

endif # end of include cache file

ifdef DEBUG
  $(info bpf-iter-cflags = ${bpf-iter-cflags})
endif

endif
