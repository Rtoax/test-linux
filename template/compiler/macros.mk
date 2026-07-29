# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
# - CC=[cc]
# - CROSS_COMPILE=
# - CC_MACHINE_CFLAGS=
#
# Functions:
# - __gen_compiler_macro_hdr()
# - gen_compiler_macro_hdr()
#
ifndef _COMPILER_MACROS_MK
_COMPILER_MACROS_MK = 1

include compiler/machine.mk

ifndef CROSS_COMPILE
  MNATIVE := ${CC_MACHINE_CFLAGS}
endif

# $(1) - compiler, CC or CXX
# $(2) - output file name
define __gen_compiler_macro_hdr
$(1) ${MNATIVE} -E -dM - </dev/null -o $(2)
endef

# $(1) - output file name
define gen_compiler_macro_hdr
$(call __gen_compiler_macro_hdr,$(CC),$(1))
endef

endif
