# SPDX-License-Identifier: GPL-3.0
SHELL = bash

NUMACTL := numactl

# Get numactl version
NUMACTL_VERSION := $(shell ${NUMACTL} --version 2>/dev/null \
		| grep -o [0-9]*\.[0-9]*\.[0-9]* | sed -n '1p' || true)

# numactl <= 2.0.14 don't has --version argument.
ifeq (${NUMACTL_VERSION},)
  NUMACTL_VERSION := $(shell rpm -q --queryformat=%{VERSION} ${NUMACTL} 2>/dev/null || true)
endif

NUMACTL_VERSION_MAJOR := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$1}')
NUMACTL_VERSION_MINOR := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$2}')
NUMACTL_VERSION_PATCH := $(shell echo ${NUMACTL_VERSION} | awk -F '.' '{print $$3}')

$(info numactl version ${NUMACTL_VERSION_MAJOR}.${NUMACTL_VERSION_MINOR}.${NUMACTL_VERSION_PATCH})
ifneq (${NUMACTL_VERSION_MAJOR},2)
  $(error Not support numactl ${NUMACTL_VERSION})
endif

