# SPDX-License-Identifier: GPL-3.0
_PAHOLE = 1

PAHOLE := $(shell which pahole 2>/dev/null)
ifeq ($(PAHOLE),)
  $(error "Not found pahole, install first")
endif

PAHOLE_VERSION := $(shell ${PAHOLE} --version | grep -o -E '[0-9].[0-9]*?')
PAHOLE_VERSION_MAJOR := $(shell echo ${PAHOLE_VERSION} | awk -F '.' '{print $$1}')
PAHOLE_VERSION_MINOR := $(shell echo ${PAHOLE_VERSION} | awk -F '.' '{print $$2}')

ifdef DEBUG
  $(info ${PAHOLE} version ${PAHOLE_VERSION_MAJOR}.${PAHOLE_VERSION_MINOR})
endif

ifneq (${PAHOLE_VERSION},${PAHOLE_VERSION_MAJOR}.${PAHOLE_VERSION_MINOR})
  $(error FATAL: parse ${PAHOLE} version failed, ${PAHOLE_VERSION} != ${PAHOLE_VERSION_MAJOR}.${PAHOLE_VERSION_MINOR})
endif

export PAHOLE PAHOLE_VERSION_MAJOR PAHOLE_VERSION_MINOR

# see linux:scripts/pahole-version.sh,scripts/Makefile.btf
pahole-ver := $(shell ${PAHOLE} --version | sed -E 's/v([0-9]+)\.([0-9]+)/\1\2/')
ifdef DEBUG
  $(info pahole-ver = ${pahole-ver})
endif

# https://git.kernel.org/pub/scm/devel/pahole/pahole.git use dwarves cmake macros
DWARVES_MINOR_VERSION := ${PAHOLE_VERSION_MAJOR}
DWARVES_MINOR_VERSION := ${PAHOLE_VERSION_MINOR}
export DWARVES_MINOR_VERSION DWARVES_MINOR_VERSION

