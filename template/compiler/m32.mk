# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _COMPILER_M32_MK
_COMPILER_M32_MK = 1

include compiler/check.mk

CC_M32 := $(findstring y,$(call check_compiler_option_noS,$(CC),-m32))
feature-m32 := $(findstring y,$(call check_compiler_option,$(CC),-m32))

ifdef DEBUG
  $(info CC: ${CC})
  $(info CC_M32: ${CC_M32})
  $(info feature-m32 ${feature-m32})
endif

endif
