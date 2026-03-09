# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - cpu-feature-cflags=
# - CPU_HAVE_${FEATURE}=y
#
ifndef _BITS_CPU_FEATURE_MK
_BITS_CPU_FEATURE_MK = 1

include arch.mk
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

ifeq (${CPU_ARCH},aarch64)
  $(call define_cpufeature,asimd) # neon
  $(call define_cpufeature,sve)
  $(call define_cpufeature,sve2)
  # For modern AArch64 CPUs that conform to the ARMv8-A and above architecture
  # specifications, ASIMD is a mandatory built-in baseline feature, not an
  # optional extension.
  ifndef CPU_HAVE_ASIMD
    $(error "Not found asimd(neon) in your CPU, please check with 'lscpu'")
  endif
else ifeq (${CPU_ARCH},x86_64)
  $(call define_cpufeature,avx2)
  $(call define_cpufeature,avx512f)
  $(call define_cpufeature,sgx)
# MORE
endif

ifdef DEBUG
  $(info cpu-feature-cflags = ${cpu-feature-cflags})
endif

endif
