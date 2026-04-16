# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - HAVE_BPFTOOL=[y]
# - BPFTOOL=[/usr/sbin/bpftool]
# - BPFTOOL_MAJOR=
# - BPFTOOL_MINOR=
#
ifndef _BPF_BPFTOOL_MK
_BPF_BPFTOOL_MK = 1

include dir.mk

BPFTOOL := $(shell which bpftool 2>/dev/null)
ifeq ($(BPFTOOL),)
  $(warning "Not found bpftool, please install it first")
  export HAVE_BPFTOOL := n
else

versh := ${TOPDIR}/scripts/version/bpftool.sh

BPFTOOL_VERSION := $(shell ${versh})
BPFTOOL_MAJOR := $(shell ${versh} --major)
BPFTOOL_MINOR := $(shell ${versh} --minor)
BPFTOOL_PATCHLEVEL := $(shell ${versh} --patchlevel)

ifdef DEBUG
  $(info BPFTOOL: ${BPFTOOL} version ${BPFTOOL_MAJOR}.${BPFTOOL_MINOR}.${BPFTOOL_PATCHLEVEL})
  $(info BPFTOOL_VERSION = ${BPFTOOL_VERSION})
  $(info BPFTOOL_MAJOR = ${BPFTOOL_MAJOR})
  $(info BPFTOOL_MINOR = ${BPFTOOL_MINOR})
  $(info BPFTOOL_PATCHLEVEL = ${BPFTOOL_PATCHLEVEL})
endif

export HAVE_BPFTOOL := y
export BPFTOOL BPFTOOL_MAJOR BPFTOOL_MINOR

endif # end of Found BPFTOOL

endif
