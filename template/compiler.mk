# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2025 Rong Tao
#
# Output definitions:
# - cflags-support-types-y
# - cflags-support-headers-y
# - ldflags-support-headers-y
#
_COMPILER_MK = 1

include shell.mk
include bits/compiler-feature.mk

CC ?= gcc
CXX ?= c++

ifndef CROSS_COMPILE
  MARCH_NATIVE := -march=native
endif
# $(1) - compiler, CC or CXX
# $(2) - output file name
define __gen_compiler_macro_hdr
	$(1) ${MARCH_NATIVE} -E -dM - </dev/null -o $(2)
endef

# $(1) - output file name
define gen_compiler_macro_hdr
$(call __gen_compiler_macro_hdr,$(CC),$(1))
endef

cflags-support-types-y :=
cflags-support-types-${CC__Float16} += -DSUPPORT__Float16=1
cflags-support-types-${CC___fp16} += -DSUPPORT___fp16=1
cflags-support-types-${CC___bf16} += -DSUPPORT___bf16=1
cflags-support-types-${CC___float128} += -DSUPPORT___float128=1
cflags-support-types-${CC__Float128} += -DSUPPORT__Float128=1
cflags-support-types-${CC___float80} += -DSUPPORT___float80=1
cflags-support-types-${CC___uint128_t} += -DSUPPORT___uint128_t=1

cflags-support-headers-y :=
cflags-support-headers-${CC_H_quadmath_h} += -DSUPPORT_quadmath_h=1
ldflags-support-headers-y :=
ldflags-support-headers-${CC_H_quadmath_h} += -lquadmath

CC_FULLVERSION := $(shell $(CC) -dumpfullversion -dumpversion)
CC_VERSION := $(shell $(CC) -dumpversion)
CC_MAJOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$1}')
CC_MINOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$2}')

ifdef DEBUG
  $(info CC: $(CC) ${CC_MAJOR}.${CC_MINOR} ${CC_FULLVERSION} ${CC_VERSION})
  $(info cflags-support-types-y: ${cflags-support-types-y})
  $(info cflags-support-headers-y: ${cflags-support-headers-y})
  $(info ldflags-support-headers-y: ${ldflags-support-headers-y})
endif
