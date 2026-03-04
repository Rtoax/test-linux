# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_BPFTRACE=[y|n]
# - BPFTRACE=[/usr/bin/bpftrace]
# - BPFTRACE_VERSION_MAJOR=
# - BPFTRACE_VERSION_MINOR=
#
ifndef _BPFTRACE_MK
_BPFTRACE_MK = 1

BPFTRACE := $(shell which bpftrace 2>/dev/null)
ifeq ($(BPFTRACE),)
  ifndef __IGNORE_NOTFOUND_ERROR__
    $(error "Not found bpftrace, install first")
  else
    $(warning "Not found bpftrace, skipping")
  endif
  export HAVE_BPFTRACE := n
else

include dir.mk

BPFTRACE_VERSION := $(shell ${TOPDIR}/bpf/bpftrace/version.sh)
BPFTRACE_VERSION_MAJOR := $(shell ${TOPDIR}/bpf/bpftrace/version.sh --major)
BPFTRACE_VERSION_MINOR := $(shell ${TOPDIR}/bpf/bpftrace/version.sh --minor)
BPFTRACE_VERSION_PATCHLEVEL := $(shell ${TOPDIR}/bpf/bpftrace/version.sh --patchlevel)

ifdef DEBUG
  $(info BPFTRACE = ${BPFTRACE})
  $(info BPFTRACE_VERSION_MAJOR = ${BPFTRACE_VERSION_MAJOR})
  $(info BPFTRACE_VERSION_MINOR = ${BPFTRACE_VERSION_MINOR})
  $(info BPFTRACE_VERSION_PATCHLEVEL = ${BPFTRACE_VERSION_PATCHLEVEL})
endif

export HAVE_BPFTRACE := y
export BPFTRACE
export BPFTRACE_VERSION_MAJOR BPFTRACE_VERSION_MINOR BPFTRACE_VERSION_PATCHLEVEL

endif # End of Found bpftrace

endif
