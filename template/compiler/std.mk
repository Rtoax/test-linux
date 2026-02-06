# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _COMPILER_STD_MK
_COMPILER_STD_MK = 1

include compiler/check.mk

CC_STD_C11 := $(findstring y,$(call check_compiler_option,$(CC),-std=c11))
CC_STD_GNU11 := $(findstring y,$(call check_compiler_option,$(CC),-std=gnu11))
CC_STD_C17 := $(findstring y,$(call check_compiler_option,$(CC),-std=c17))
CC_STD_GNU17 := $(findstring y,$(call check_compiler_option,$(CC),-std=gnu17))
CC_STD_GNU++20 := $(findstring y,$(call check_compiler_option,$(CC),-std=gnu++20))
CC_STD_C++20 := $(findstring y,$(call check_compiler_option,$(CC),-std=c++20))

ifdef DEBUG
  $(info CC: ${CC})
  $(info CC_STD_C11: ${CC_STD_C11})
  $(info CC_STD_GNU11: ${CC_STD_GNU11})
  $(info CC_STD_C17: ${CC_STD_C17})
  $(info CC_STD_GNU17: ${CC_STD_GNU17})
  $(info CC_STD_GNU++20: ${CC_STD_GNU++20})
  $(info CC_STD_C++20: ${CC_STD_C++20})
endif

endif
