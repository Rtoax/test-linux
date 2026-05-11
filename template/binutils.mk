# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
#
# Definitions:
# - LD_BFD=[/usr/bin/ld.bfd]
# - HAVE_LD_BFD=[y|n]
# - BINUTILS_VERSION=
# - BINUTILS_MAJOR=
# - BINUTILS_MINOR=
# - binutils-cflags=
#
ifndef _BINUTILS_MK
_BINUTILS_MK = 1

include dir.mk
include define.mk

binutils-cflags :=

$(call find_cmd_and_def,ld.bfd)

ifeq ($(LD_BFD),)
  $(warning "Not found linker ld.bfd, install binutils first")
endif

binutilsversh = ${TOPDIR}/scripts/version/binutils.sh

# Get binutils version
BINUTILS_VERSION := $(shell ${binutilsversh})
BINUTILS_MAJOR := $(shell ${binutilsversh} --major)
BINUTILS_MINOR := $(shell ${binutilsversh} --minor)

binutils-cflags += -DBINUTILS_MAJOR=${BINUTILS_MAJOR}
binutils-cflags += -DBINUTILS_MINOR=${BINUTILS_MINOR}

ifdef DEBUG
  $(info Binutils version ${BINUTILS_MAJOR}.${BINUTILS_MINOR})
  $(info BINUTILS_VERSION = ${BINUTILS_VERSION})
  $(info BINUTILS_MAJOR = ${BINUTILS_MAJOR})
  $(info BINUTILS_MINOR = ${BINUTILS_MINOR})
  $(info binutils-cflags = ${binutils-cflags})
endif

ifneq (${BINUTILS_MAJOR},2)
  $(error Not support binutils major=${BINUTILS_VERSION}, only major==2)
endif

export BINUTILS_VERSION
export BINUTILS_MAJOR
export BINUTILS_MINOR
export binutils-cflags

endif
