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
include file.mk

cachefile := ${TOPDIR}/template/compiler/.feature.mk.cache
origfile := ${TOPDIR}/template/compiler/feature.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else
include bits/mk-cache.mk

feature-mavx2 := $(findstring y,$(call compiler_support_option,$(CC),-mavx2))
feature-mfentry := $(findstring y,$(call compiler_support_option,$(CC),-mfentry))
feature-sve2 := $(findstring y,$(call compiler_support_option,$(CC),-march=armv8-a+sve+sve2))
feature-mavx512f := $(findstring y,$(call compiler_support_option,$(CC),-mavx512f))
feature-lse := $(findstring y,$(call compiler_support_option,$(CC),-march=armv8-a+lse))
feature-fcf-protection := $(findstring y,$(call compiler_support_option,$(CC),-fcf-protection))
feature-fpatchable-function-entry := $(findstring y,$(call compiler_support_option,$(CC),-fpatchable-function-entry=5,2))

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
