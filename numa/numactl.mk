# SPDX-License-Identifier: GPL-3.0
SHELL = bash

NUMACTL := numactl

# Get numactl version
NUMACTL_VERSION := $(shell ${NUMACTL} --version | grep -o [0-9]*\.[0-9]*\.[0-9]* | sed -n '1p' || true)

NUMACTL_VERSION_MAJOR := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$1}')
NUMACTL_VERSION_MINOR := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$2}')
NUMACTL_VERSION_PATCH := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$2}')

$(info numactl version ${NUMACTL_VERSION_MAJOR}.${NUMACTL_VERSION_MINOR}.${NUMACTL_VERSION_PATCH})
ifneq (${NUMACTL_VERSION_MAJOR},2)
  $(error Not support binutils ${NUMACTL_VERSION})
endif

