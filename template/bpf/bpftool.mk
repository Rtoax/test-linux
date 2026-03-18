# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - HAVE_BPFTOOL=[y]
# - BPFTOOL=[/usr/sbin/bpftool]
# - BPFTOOL_VERSION_MAJOR=
# - BPFTOOL_VERSION_MINOR=
#
ifndef _BPF_BPFTOOL_MK
_BPF_BPFTOOL_MK = 1

include dir.mk

BPFTOOL := $(shell which bpftool 2>/dev/null)
ifeq ($(BPFTOOL),)
  $(warning "Not found bpftool, please install it first")
  export HAVE_BPFTOOL := n
else

BPFTOOL_VERSION := $(shell ${TOPDIR}/scripts/version/bpftool.sh)
BPFTOOL_VERSION_MAJOR := $(shell echo ${BPFTOOL_VERSION} | awk -F '.' '{print $$1}')
BPFTOOL_VERSION_MINOR := $(shell echo ${BPFTOOL_VERSION} | awk -F '.' '{print $$2}')

ifdef DEBUG
  $(info BPFTOOL: ${BPFTOOL} version ${BPFTOOL_VERSION_MAJOR}.${BPFTOOL_VERSION_MINOR})
endif

export HAVE_BPFTOOL := y
export BPFTOOL BPFTOOL_VERSION_MAJOR BPFTOOL_VERSION_MINOR

endif # end of Found BPFTOOL

endif
