# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
#
# Input definitions:
# - CROSS_COMPILE=
# - CC=[cc]
# - CXX=[c++]
#
# Output definitions:
# - CC_FULLVERSION=
# - CC_VERSION=
# - CC_MAJOR=
# - CC_MINOR=
# - CC_PATCHLEVEL=
# - cflags-support-types-y=
# - cflags-support-headers-y=
# - ldflags-support-headers-y=
#
ifndef _COMPILER_MK
_COMPILER_MK = 1

include shell.mk
include compiler/feature.mk
include compiler/std.mk
include compiler/m32.mk
include compiler/macros.mk
include compiler/types.mk

cachefile := ${TOPDIR}/template/.compiler.mk.cache

ifneq ($(wildcard ${cachefile}),)
  include ${cachefile}
else

cflags-support-types-y :=
cflags-support-headers-y :=
ldflags-support-headers-y :=

cflags-support-types-${CC__Float16} += -DSUPPORT__Float16=1
cflags-support-types-${CC__Float32} += -DSUPPORT__Float32=1
cflags-support-types-${CC__Float64} += -DSUPPORT__Float64=1
cflags-support-types-${CC___fp16} += -DSUPPORT___fp16=1
cflags-support-types-${CC___bf16} += -DSUPPORT___bf16=1
cflags-support-types-${CC___float128} += -DSUPPORT___float128=1
cflags-support-types-${CC__Float128} += -DSUPPORT__Float128=1
cflags-support-types-${CC___float80} += -DSUPPORT___float80=1
cflags-support-types-${CC___uint128_t} += -DSUPPORT___uint128_t=1

cflags-support-headers-${CC_H_quadmath_h} += -DSUPPORT_quadmath_h=1
ldflags-support-headers-${CC_lquadmath} += -lquadmath

CC_FULLVERSION := $(shell $(CC) -dumpfullversion -dumpversion)
CC_VERSION := $(shell $(CC) -dumpversion)
CC_MAJOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$1}')
CC_MINOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$2}')
CC_PATCHLEVEL := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$3}')

# Save to cache
include bits/mk-cache.mk
$(call mk_cache_var,cflags-support-types-y,${cachefile})
$(call mk_cache_var,cflags-support-headers-y,${cachefile})
$(call mk_cache_var,ldflags-support-headers-y,${cachefile})

$(call mk_cache_var,CC_FULLVERSION,${cachefile})
$(call mk_cache_var,CC_VERSION,${cachefile})
$(call mk_cache_var,CC_MAJOR,${cachefile})
$(call mk_cache_var,CC_MINOR,${cachefile})
$(call mk_cache_var,CC_PATCHLEVEL,${cachefile})

endif # end of cache file exist

ifdef DEBUG
  $(info CC: $(CC) ${CC_MAJOR}.${CC_MINOR}.${CC_PATCHLEVEL} ${CC_FULLVERSION} ${CC_VERSION})
  $(info cflags-support-types-y: ${cflags-support-types-y})
  $(info cflags-support-headers-y: ${cflags-support-headers-y})
  $(info ldflags-support-headers-y: ${ldflags-support-headers-y})
endif

export CC_FULLVERSION
export CC_VERSION
export CC_MAJOR
export CC_MINOR
export CC_PATCHLEVEL
export cflags-support-types-y
export cflags-support-headers-y
export ldflags-support-headers-y

endif
