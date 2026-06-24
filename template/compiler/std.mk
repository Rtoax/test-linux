# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _COMPILER_STD_MK
_COMPILER_STD_MK = 1

include compiler/check.mk
include file.mk

cachefile := ${TOPDIR}/template/compiler/.std.mk.cache
origfile := ${TOPDIR}/template/compiler/std.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else
include bits/mk-cache.mk

CC_STD_C11 := $(findstring y,$(call compiler_support_option,$(CC),-std=c11))
CC_STD_GNU11 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu11))
CC_STD_C17 := $(findstring y,$(call compiler_support_option,$(CC),-std=c17))
CC_STD_GNU17 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu17))
CC_STD_C23 := $(findstring y,$(call compiler_support_option,$(CC),-std=c23))
CC_STD_GNU23 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu23))
CC_STD_C26 := $(findstring y,$(call compiler_support_option,$(CC),-std=c26))
CC_STD_GNU26 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu26))

CC_STD_GNU++11 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu++11))
CC_STD_C++11 := $(findstring y,$(call compiler_support_option,$(CC),-std=c++11))
CC_STD_GNU++14 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu++14))
CC_STD_C++14 := $(findstring y,$(call compiler_support_option,$(CC),-std=c++14))
CC_STD_GNU++17 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu++17))
CC_STD_C++17 := $(findstring y,$(call compiler_support_option,$(CC),-std=c++17))
CC_STD_GNU++03 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu++03))
CC_STD_C++03 := $(findstring y,$(call compiler_support_option,$(CC),-std=c++03))
CC_STD_GNU++20 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu++20))
CC_STD_C++20 := $(findstring y,$(call compiler_support_option,$(CC),-std=c++20))
CC_STD_GNU++23 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu++23))
CC_STD_C++23 := $(findstring y,$(call compiler_support_option,$(CC),-std=c++23))
CC_STD_GNU++26 := $(findstring y,$(call compiler_support_option,$(CC),-std=gnu++26))
CC_STD_C++26 := $(findstring y,$(call compiler_support_option,$(CC),-std=c++26))

$(call mk_cache_var,CC_STD_C11,${cachefile})
$(call mk_cache_var,CC_STD_GNU11,${cachefile})
$(call mk_cache_var,CC_STD_C17,${cachefile})
$(call mk_cache_var,CC_STD_GNU17,${cachefile})
$(call mk_cache_var,CC_STD_C23,${cachefile})
$(call mk_cache_var,CC_STD_GNU23,${cachefile})
$(call mk_cache_var,CC_STD_C26,${cachefile})
$(call mk_cache_var,CC_STD_GNU26,${cachefile})

$(call mk_cache_var,CC_STD_GNU++11,${cachefile})
$(call mk_cache_var,CC_STD_C++11,${cachefile})
$(call mk_cache_var,CC_STD_GNU++14,${cachefile})
$(call mk_cache_var,CC_STD_C++14,${cachefile})
$(call mk_cache_var,CC_STD_GNU++17,${cachefile})
$(call mk_cache_var,CC_STD_C++17,${cachefile})
$(call mk_cache_var,CC_STD_GNU++03,${cachefile})
$(call mk_cache_var,CC_STD_C++03,${cachefile})
$(call mk_cache_var,CC_STD_GNU++20,${cachefile})
$(call mk_cache_var,CC_STD_C++20,${cachefile})
$(call mk_cache_var,CC_STD_GNU++23,${cachefile})
$(call mk_cache_var,CC_STD_C++23,${cachefile})
$(call mk_cache_var,CC_STD_GNU++26,${cachefile})
$(call mk_cache_var,CC_STD_C++26,${cachefile})

endif # end of cache file exist

ifdef DEBUG
  $(info CC: ${CC})
  $(info CC_STD_C11: ${CC_STD_C11})
  $(info CC_STD_GNU11: ${CC_STD_GNU11})
  $(info CC_STD_C17: ${CC_STD_C17})
  $(info CC_STD_GNU17: ${CC_STD_GNU17})
  $(info CC_STD_C23: ${CC_STD_C23})
  $(info CC_STD_GNU23: ${CC_STD_GNU23})
  $(info CC_STD_C26: ${CC_STD_C26})
  $(info CC_STD_GNU26: ${CC_STD_GNU26})
  $(info CC_STD_GNU++11: ${CC_STD_GNU++11})
  $(info CC_STD_C++11: ${CC_STD_C++11})
  $(info CC_STD_GNU++14: ${CC_STD_GNU++14})
  $(info CC_STD_C++14: ${CC_STD_C++14})
  $(info CC_STD_GNU++17: ${CC_STD_GNU++17})
  $(info CC_STD_C++17: ${CC_STD_C++17})
  $(info CC_STD_GNU++03: ${CC_STD_GNU++03})
  $(info CC_STD_C++03: ${CC_STD_C++03})
  $(info CC_STD_GNU++20: ${CC_STD_GNU++20})
  $(info CC_STD_C++20: ${CC_STD_C++20})
  $(info CC_STD_GNU++23: ${CC_STD_GNU++23})
  $(info CC_STD_C++23: ${CC_STD_C++23})
  $(info CC_STD_GNU++26: ${CC_STD_GNU++26})
  $(info CC_STD_C++26: ${CC_STD_C++26})
endif

endif
