# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_BPFTRACE=[y|n]
# - BPFTRACE=[/usr/bin/bpftrace]
# - BPFTRACE_MAJOR=
# - BPFTRACE_MINOR=
# - BPFTRACE_PATCHLEVEL=
#
# Functions:
# - bpftrace_{gt,ge,eq,lt,le}(major,minor,patchlevel)=[y|n]
#
ifndef _BPFTRACE_MK
_BPFTRACE_MK = 1

BPFTRACE := $(shell which bpftrace 2>/dev/null)
ifeq ($(BPFTRACE),)
  $(warning "Not found bpftrace, please install bpftrace")
  export HAVE_BPFTRACE := n
else

include dir.mk
include version.mk

bpftraceversh = ${TOPDIR}/scripts/version/bpftrace.sh

BPFTRACE_VERSION := $(shell ${bpftraceversh})
BPFTRACE_MAJOR := $(shell ${bpftraceversh} --major)
BPFTRACE_MINOR := $(shell ${bpftraceversh} --minor)
BPFTRACE_PATCHLEVEL := $(shell ${bpftraceversh} --patchlevel)

$(eval $(call define_version,bpftrace,version3_code1688,${BPFTRACE_MAJOR},${BPFTRACE_MINOR},${BPFTRACE_PATCHLEVEL}))

ifdef DEBUG
  $(info BPFTRACE = ${BPFTRACE})
  $(info BPFTRACE_MAJOR = ${BPFTRACE_MAJOR})
  $(info BPFTRACE_MINOR = ${BPFTRACE_MINOR})
  $(info BPFTRACE_PATCHLEVEL = ${BPFTRACE_PATCHLEVEL})
endif

# The newest bpftrace is 0.25.0 right now.
ifneq ($(call bpftrace_lt,0,26,0),y)
  $(error "Call bpftrace_lt failed, $(call bpftrace,0,26,0)")
endif

export HAVE_BPFTRACE := y
export BPFTRACE
export BPFTRACE_MAJOR BPFTRACE_MINOR BPFTRACE_PATCHLEVEL

endif # End of Found bpftrace

endif
