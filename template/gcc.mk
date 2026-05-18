# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
#
# Output definitions:
# - HAVE_GCC=[y|n]
# - HAVE_GXX=[y|n]
# - GCC=[/usr/bin/gcc]
# - GXX=[/usr/bin/g++]
# - GCC_VERSION=
# - GCC_MAJOR=
# - GCC_MINOR=
# - GCC_PATCHLEVEL=
#
# Functions:
# - gcc_{gt,ge,eq,lt,le}()=[y|n]
#
ifndef _GCC_MK
_GCC_MK = 1

include dir.mk
include define.mk
include shell.mk
include version.mk

$(call find_cmd_and_def,gcc)
$(call find_cmd_and_def,g++,gxx)

CC ?= ${GCC}
CXX ?= ${GXX}

gccversh = ${TOPDIR}/scripts/version/gcc.sh

GCC_VERSION := $(shell ${gccversh})
GCC_MAJOR := $(shell ${gccversh} --major)
GCC_MINOR := $(shell ${gccversh} --minor)
GCC_PATCHLEVEL := $(shell ${gccversh} --patchlevel)

include compiler.mk

$(eval $(call define_version,gcc,version3_code1688,${GCC_MAJOR},${GCC_MINOR},${GCC_PATCHLEVEL}))

ifdef DEBUG
  $(info GCC = ${GCC})
  $(info GXX = ${GXX})
  $(info GCC_VERSION = ${GCC_VERSION} (${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL}))
endif

# Do some checks
ifneq (${GCC_VERSION},${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
  $(error Failed to parse GCC version, ${GCC_VERSION} != ${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
endif

# newest gcc major is 16
ifneq ($(call gcc_gt,17,0,0), n)
  $(error call gcc_gt failed, $(call gcc_gt,17,0,0))
endif

export GCC GXX
export GCC_VERSION GCC_MAJOR GCC_MINOR GCC_PATCHLEVEL

endif
