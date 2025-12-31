# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Output definitions:
# - cpu-feature-cflags=
# - CPU_HAVE_${FEATURE}=y
#
_BITS_CPU_FEATURE_MK = 1

include string.mk

# $1: cpu feature, like avx512f
define ___define_cpufeature
  ifeq ($(shell lscpu | grep -wo ${1} >/dev/null && echo y),y)
    export CPU_HAVE_$(call toupper_shell,$(1)) := y
    cpu-feature-cflags += -DCPU_HAVE_$(call toupper_shell,$(1))=1
    $(info CPU have ${1})
  endif
endef
define define_cpufeature
  $(eval $(call ___define_cpufeature,${1}))
endef

$(call define_cpufeature,avx2)
$(call define_cpufeature,avx512f)
$(call define_cpufeature,sve)
$(call define_cpufeature,sve2)
$(call define_cpufeature,asimd) # neon

ifdef DEBUG
  $(info cpu-feature-cflags = ${cpu-feature-cflags})
endif
