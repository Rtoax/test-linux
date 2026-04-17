# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
#
ifndef _BINUTILS_MK
_BINUTILS_MK = 1

include dir.mk

LD_BFD := $(shell which ld.bfd 2>/dev/null)
ifeq ($(LD_BFD),)
  $(warning "Not found linker ld.bfd, install binutils first")
endif

binutilsversh = ${TOPDIR}/scripts/version/binutils

# Get binutils version
BINUTILS_VERSION := $(shell ${binutilsversh})
BINUTILS_VERSION_MAJOR := $(shell ${binutilsversh} --major)
BINUTILS_VERSION_MINOR := $(shell ${binutilsversh} --minor)

ifneq (${BINUTILS_VERSION_MAJOR},2)
  $(error Not support binutils major=${BINUTILS_VERSION})
endif

ifdef DEBUG
  $(info LD_BFD = ${LD_BFD})
  $(info BINUTILS_VERSION = ${BINUTILS_VERSION})
  $(info Binutils version ${BINUTILS_VERSION_MAJOR}.${BINUTILS_VERSION_MINOR})
endif

endif
