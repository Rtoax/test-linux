# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - NUMACTL=[/usr/bin/numactl]
# - HAVE_NUMACTL=[y|n]
# - HAVE_LIBNUMA=[y|n]
# - NUMACTL_MAJOR=
# - NUMACTL_MINOR=
# - NUMACTL_PATCH=
#
ifndef _NUMACTL_MK
_NUMACTL_MK = 1

include dir.mk
include shell.mk
include define.mk

$(call find_cmd_and_def,numactl)

LIBNUMA_HDR := /usr/include/numa.h
LIBNUMAIF_HDR := /usr/include/numaif.h

ifeq (${NUMACTL},)
  $(warning Not found numactl, please install first)
  export HAVE_LIBNUMA := n
else
# Get numactl version
NUMACTL_VERSION := $(shell ${TOPDIR}/scripts/version/numactl.sh)

$(call check_file_and_def,${LIBNUMA_HDR},HAVE_LIBNUMA)

NUMACTL_MAJOR := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$1}')
NUMACTL_MINOR := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$2}')
NUMACTL_PATCH := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$3}')

ifdef DEBUG
  $(info numactl version ${NUMACTL_MAJOR}.${NUMACTL_MINOR}.${NUMACTL_PATCH})
endif

ifneq (${NUMACTL_MAJOR},2)
  $(error Not support numactl ${NUMACTL_VERSION})
endif

export HAVE_LIBNUMA := y
export NUMACTL_MAJOR NUMACTL_MINOR NUMACTL_PATCH
endif # end of found NUMACTL

endif # end of _NUMACTL_MK
