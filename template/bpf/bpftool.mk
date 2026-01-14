# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - HAVE_BPFTOOL=[y]
# - BPFTOOL=
# - BPFTOOL_VERSION_MAJOR=
# - BPFTOOL_VERSION_MINOR=
#
ifndef _BPF_BPFTOOL_MK
_BPF_BPFTOOL_MK = 1

include dir.mk

BPFTOOL := $(shell which bpftool 2>/dev/null)
ifeq ($(BPFTOOL),)
  $(error "Not found bpftool, install first")
else
  export HAVE_BPFTOOL := y

  BPFTOOL_VERSION := $(shell ${TOPDIR}/bpf/bpftool/version.sh)
  BPFTOOL_VERSION_MAJOR := $(shell echo ${BPFTOOL_VERSION} | awk -F '.' '{print $$1}')
  BPFTOOL_VERSION_MINOR := $(shell echo ${BPFTOOL_VERSION} | awk -F '.' '{print $$2}')

  export BPFTOOL BPFTOOL_VERSION_MAJOR BPFTOOL_VERSION_MINOR
endif


ifdef DEBUG
  $(info BPFTOOL: ${BPFTOOL} version ${BPFTOOL_VERSION_MAJOR}.${BPFTOOL_VERSION_MINOR})
endif

endif
