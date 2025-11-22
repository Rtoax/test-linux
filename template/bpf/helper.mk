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

export bpf-helper-cflags

ifdef DEBUG
  $(info bpf-helper-cflags = ${bpf-helper-cflags})
endif
