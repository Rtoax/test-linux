# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
#
ifndef _BINUTILS_MK
export _BINUTILS_MK = 1

include dir.mk

LD_BFD := $(shell which ld.bfd 2>/dev/null)
ifeq ($(LD_BFD),)
  $(warning "Not found linker ld.bfd, install binutils first")
endif

# Get binutils version
BINUTILS_VERSION := $(shell ${TOPDIR}/gnu/binutils/version.sh)
BINUTILS_VERSION_MAJOR := $(shell ${TOPDIR}/gnu/binutils/version.sh --major)
BINUTILS_VERSION_MINOR := $(shell ${TOPDIR}/gnu/binutils/version.sh --minor)

ifneq (${BINUTILS_VERSION_MAJOR},2)
  $(error Not support binutils major=${BINUTILS_VERSION})
endif

ifdef DEBUG
  $(info LD_BFD = ${LD_BFD})
  $(info Binutils version ${BINUTILS_VERSION_MAJOR}.${BINUTILS_VERSION_MINOR})
endif

endif
