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
  $(eval $(call ___define_helper,bpf_strncmp))
endef

# linux v5.16-rc4-1160-gc5fb19937455
# commit c5fb19937455 ("bpf: Add bpf_strncmp helper")
ifeq ($(call kver_gt,5,16,0),y)
  $(call define_helper,bpf_strncmp)
endif

export bpf-helper-cflags

ifdef DEBUG
  $(info bpf-helper-cflags = ${bpf-helper-cflags})
endif
