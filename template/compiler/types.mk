# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _COMPILER_TYPES_MK
_COMPILER_TYPES_MK = 1

include dir.mk
include compiler/check.mk
include file.mk

cachefile := ${TOPDIR}/template/compiler/.types.mk.cache
origfile := ${TOPDIR}/template/compiler/types.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else

# see https://clang.llvm.org/docs/LanguageExtensions.html
CC__Float16 := $(findstring y,$(call compiler_support_type,$(CC),_Float16))
CC__Float32 := $(findstring y,$(call compiler_support_type,$(CC),_Float32))
CC__Float64 := $(findstring y,$(call compiler_support_type,$(CC),_Float64))
CC___fp16 := $(findstring y,$(call compiler_support_type,$(CC),__fp16))
CC___bf16 := $(findstring y,$(call compiler_support_type,$(CC),__bf16))
# GCC Additional Floating Types: https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html
# - NVRTC on Linux
# - GCC version 4.1 or later on x86_64/amd64
# - Clang version 3.9 or later on x86_64/amd64
# - NVHPC version 21.1 or later on x86_64/amd64
CC___float128 := $(findstring y,$(call compiler_support_type,$(CC),__float128))
CC__Float128 := $(findstring y,$(call compiler_support_type,$(CC),_Float128))
CC___float80 := $(findstring y,$(call compiler_support_type,$(CC),__float80))
CC___uint128_t := $(findstring y,$(call compiler_support_type,$(CC),__uint128_t))

CC_lquadmath := $(findstring y,$(call compiler_support_option_link,$(CC),-lquadmath))
CC_H_quadmath_h := $(findstring y,$(call compiler_support_header,$(CC),quadmath.h))

include bits/mk-cache.mk

$(call make_append_var_to_file,CC__Float16,${cachefile})
$(call make_append_var_to_file,CC__Float32,${cachefile})
$(call make_append_var_to_file,CC__Float64,${cachefile})
$(call make_append_var_to_file,CC___fp16,${cachefile})
$(call make_append_var_to_file,CC___bf16,${cachefile})
$(call make_append_var_to_file,CC___float128,${cachefile})
$(call make_append_var_to_file,CC__Float128,${cachefile})
$(call make_append_var_to_file,CC___float80,${cachefile})
$(call make_append_var_to_file,CC___uint128_t,${cachefile})

endif # end of cache file exist

ifdef DEBUG
  $(info CC: ${CC})
  $(info CC__Float16: ${CC__Float16})
  $(info CC__Float32: ${CC__Float32})
  $(info CC__Float64: ${CC__Float64})
  $(info CC___fp16: ${CC___fp16})
  $(info CC___bf16: ${CC___bf16})
  $(info CC___float128: ${CC___float128})
  $(info CC__Float128: ${CC__Float128})
  $(info CC___float80: ${CC___float80})
  $(info CC___uint128_t: ${CC___uint128_t})

  $(info CC_lquadmath: ${CC_lquadmath})
  $(info CC_H_quadmath_h: ${CC_H_quadmath_h})
endif

endif
