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

# Use cache first if it's exist, because it's fast,
cachefile := ${TOPDIR}/template/bpf/.iter.mk.cache
ifneq ($(wildcard ${cachefile}),)
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
  $(call mk_cache_var,SUPPORT_$(call toupper_shell,${1}),${cachefile})
endef

# linux v6.12-rc1-177-g4971266e1595
# commit 4971266e1595 ("bpf: Add kmem_cache iterator")
ifeq ($(call kver_ge,6,13,0),y)
  $(call bpf_def_iter,iter_kmem_cache)
endif

# linux v5.7-rc2-1180-geaaacd23910f
# commit eaaacd23910f ("bpf: Add task and task/file iterator targets")
ifeq ($(call kver_ge,5,7,0),y)
  $(call bpf_def_iter,iter_task)
  $(call bpf_def_iter,iter_task_file)
endif

$(call mk_cache_var,bpf-iter-cflags,${cachefile})

endif # end of include cache file

ifdef DEBUG
  $(info bpf-iter-cflags = ${bpf-iter-cflags})
endif

endif
