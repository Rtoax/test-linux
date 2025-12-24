# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - NUMACTL=
# - HAVE_LIBNUMA=y
# - NUMACTL_VERSION_MAJOR=
# - NUMACTL_VERSION_MINOR=
# - NUMACTL_VERSION_PATCH=
#
_NUMACTL = 1

include dir.mk
include shell.mk
include define.mk

NUMACTL := $(shell which numactl 2>/dev/null || :)
LIBNUMA_HDR := /usr/include/numa.h
LIBNUMAIF_HDR := /usr/include/numaif.h

ifneq (${NUMACTL},)
  # Get numactl version
  NUMACTL_VERSION := $(shell ${TOPDIR}/numa/numactl/version.sh)
else
  $(warning Not found numactl, please install first)
endif

$(call check_file_and_def,${LIBNUMA_HDR},HAVE_LIBNUMA)

NUMACTL_VERSION_MAJOR := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$1}')
NUMACTL_VERSION_MINOR := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$2}')
NUMACTL_VERSION_PATCH := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$3}')

ifdef DEBUG
  $(info numactl version ${NUMACTL_VERSION_MAJOR}.${NUMACTL_VERSION_MINOR}.${NUMACTL_VERSION_PATCH})
endif

ifneq (${NUMACTL_VERSION_MAJOR},2)
  $(error Not support numactl ${NUMACTL_VERSION})
endif

export NUMACTL
export NUMACTL_VERSION_MAJOR NUMACTL_VERSION_MINOR NUMACTL_VERSION_PATCH
