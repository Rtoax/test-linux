# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
#
# Export definitions
# - BINUTILS_VERSION=
# - BINUTILS_MAJOR=
# - BINUTILS_MINOR=
# - binutils-cflags=
#
ifndef _BINUTILS_MK
_BINUTILS_MK = 1

include dir.mk

binutils-cflags :=

LD_BFD := $(shell which ld.bfd 2>/dev/null)
ifeq ($(LD_BFD),)
  $(warning "Not found linker ld.bfd, install binutils first")
endif

binutilsversh = ${TOPDIR}/scripts/version/binutils

# Get binutils version
BINUTILS_VERSION := $(shell ${binutilsversh})
BINUTILS_MAJOR := $(shell ${binutilsversh} --major)
BINUTILS_MINOR := $(shell ${binutilsversh} --minor)

binutils-cflags += -DBINUTILS_MAJOR=${BINUTILS_MAJOR}
binutils-cflags += -DBINUTILS_MINOR=${BINUTILS_MINOR}

ifdef DEBUG
  $(info LD_BFD = ${LD_BFD})
  $(info Binutils version ${BINUTILS_MAJOR}.${BINUTILS_MINOR})
  $(info BINUTILS_VERSION = ${BINUTILS_VERSION})
  $(info BINUTILS_MAJOR = ${BINUTILS_MAJOR})
  $(info BINUTILS_MINOR = ${BINUTILS_MINOR})
  $(info binutils-cflags = ${binutils-cflags})
endif

ifneq (${BINUTILS_MAJOR},2)
  $(error Not support binutils major=${BINUTILS_VERSION})
endif

export BINUTILS_VERSION
export BINUTILS_MAJOR
export BINUTILS_MINOR
export binutils-cflags

endif
