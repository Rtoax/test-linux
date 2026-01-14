# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# https://git.kernel.org/pub/scm/devel/pahole/pahole.git
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output definitions:
# - PAHOLE=
# - PAHOLE_VERSION_MAJOR=DWARVES_MINOR_VERSION=
# - PAHOLE_VERSION_MINOR=DWARVES_MINOR_VERSION=
#
# Funtions:
# - pahole_version_code()=PAHOLE_VERSION_CODE
# - pahole_version_compare()=[y|n]
# - pahole_gt()=[y|n]
# - pahole_ge()=[y|n]
# - pahole_eq()=[y|n]
# - pahole_lt()=[y|n]
# - pahole_le()=[y|n]
#
ifndef _PAHOLE_MK
_PAHOLE_MK = 1

include shell.mk

PAHOLE := $(shell which pahole 2>/dev/null)
ifeq ($(PAHOLE),)
  ifndef __IGNORE_NOTFOUND_ERROR__
    $(error "Not found pahole, install first")
  else
    $(warning "Not found pahole, install first")
  endif
endif

PAHOLE_VERSION := 0.0
PAHOLE_VERSION_MAJOR := 0
PAHOLE_VERSION_MINOR := 0
DWARVES_MAJOR_VERSION := 0
DWARVES_MINOR_VERSION := 0


ifneq ($(PAHOLE),)
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
  DWARVES_MAJOR_VERSION := ${PAHOLE_VERSION_MAJOR}
  DWARVES_MINOR_VERSION := ${PAHOLE_VERSION_MINOR}

  export DWARVES_MAJOR_VERSION DWARVES_MINOR_VERSION
endif

define pahole_version_code
$(shell echo "$$(( (${1}<<16) + (${2}<<8) ))")
endef

PAHOLE_VERSION_CODE := $(call pahole_version_code,${PAHOLE_VERSION_MAJOR},${PAHOLE_VERSION_MINOR})

# Arguments:
# $1: [-gt|-ge|-eq|-lt|-le]
# $2: major
# $3: minor
define pahole_version_compare
$(shell if [[ ${PAHOLE_VERSION_CODE} ${1} $(call pahole_version_code,${2},${3}) ]]; then \
		echo y; \
	else echo n; \
	fi)
endef

define pahole_gt
$(call pahole_version_compare,-gt,${1},${2})
endef
define pahole_ge
$(call pahole_version_compare,-ge,${1},${2})
endef
define pahole_eq
$(call pahole_version_compare,-eq,${1},${2})
endef
define pahole_lt
$(call pahole_version_compare,-lt,${1},${2})
endef
define pahole_le
$(call pahole_version_compare,-le,${1},${2})
endef

# Make sure function works fine.
ifneq ($(call pahole_eq,${PAHOLE_VERSION_MAJOR},${PAHOLE_VERSION_MINOR}),y)
  $(error "Call pahole_eq failed")
endif
ifneq ($(call pahole_gt,0,0),y)
  $(error "Call pahole_gt failed")
endif
# The newest pahole is v1.31 right now.
ifneq ($(call pahole_lt,1,32),y)
  $(error "Call pahole_lt failed")
endif

endif
