# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Input definitions:
# - CC=[cc]
#
ifndef _COMPILER_FEATURE_MK
_COMPILER_FEATURE_MK = 1

include dir.mk
include compiler/check.mk
include bits/mk-cache.mk

cachefile := ${TOPDIR}/template/compiler/.feature.mk.cache

ifneq ($(wildcard ${cachefile}),)
  include ${cachefile}
else

feature-mavx2 := $(findstring y,$(call check_compiler_option,$(CC),-mavx2))
feature-mfentry := $(findstring y,$(call check_compiler_option,$(CC),-mfentry))
feature-sve2 := $(findstring y,$(call check_compiler_option,$(CC),-march=armv8-a+sve+sve2))
feature-mavx512f := $(findstring y,$(call check_compiler_option,$(CC),-mavx512f))
feature-lse := $(findstring y,$(call check_compiler_option,$(CC),-march=armv8-a+lse))
feature-fcf-protection := $(findstring y,$(call check_compiler_option,$(CC),-fcf-protection))
feature-fpatchable-function-entry := $(findstring y,$(call check_compiler_option,$(CC),-fpatchable-function-entry=5,2))

$(call mk_cache_var,feature-mavx2,${cachefile})
$(call mk_cache_var,feature-mfentry,${cachefile})
$(call mk_cache_var,feature-sve2,${cachefile})
$(call mk_cache_var,feature-mavx512f,${cachefile})
$(call mk_cache_var,feature-lse,${cachefile})
$(call mk_cache_var,feature-fcf-protection,${cachefile})
$(call mk_cache_var,feature-fpatchable-function-entry,${cachefile})

endif # end of cache file exist

ifdef DEBUG
  $(info CC: ${CC})

  $(info feature-mavx2 ${feature-mavx2})
  $(info feature-mfentry $(feature-mfentry))
  $(info feature-sve2 ${feature-sve2})
  $(info feature-mavx512f ${feature-mavx512f})
  $(info feature-lse ${feature-lse})
  $(info feature-fcf-protection ${feature-fcf-protection})
  $(info feature-fpatchable-function-entry ${feature-fpatchable-function-entry})
endif

endif
