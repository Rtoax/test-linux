# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# https://git.kernel.org/pub/scm/devel/pahole/pahole.git
#
# Output definitions:
# - HAVE_PAHOLE=[y|n]
# - PAHOLE=
# - PAHOLE_VERSION_MAJOR=DWARVES_MINOR_VERSION=
# - PAHOLE_VERSION_MINOR=DWARVES_MINOR_VERSION=
# - pahole-cflags=
#
# Funtions:
# - pahole_gt()=[y|n]
# - pahole_ge()=[y|n]
# - pahole_eq()=[y|n]
# - pahole_lt()=[y|n]
# - pahole_le()=[y|n]
#
ifndef _PAHOLE_MK
_PAHOLE_MK = 1

include dir.mk
include shell.mk
include version.mk

PAHOLE := $(shell which pahole 2>/dev/null)
ifeq ($(PAHOLE),)
  $(warning "Not found pahole, skipping")
  export HAVE_PAHOLE := n
else
export HAVE_PAHOLE := y

PAHOLE_VERSION := 0.0
PAHOLE_VERSION_MAJOR := 0
PAHOLE_VERSION_MINOR := 0
DWARVES_MAJOR_VERSION := 0
DWARVES_MINOR_VERSION := 0

paholeversh = ${TOPDIR}/scripts/version/binutils.sh

PAHOLE_VERSION := $(shell ${paholeversh})
PAHOLE_VERSION_MAJOR := $(shell ${paholeversh} --major)
PAHOLE_VERSION_MINOR := $(shell ${paholeversh} --minor)

ifdef DEBUG
  $(info ${PAHOLE} version ${PAHOLE_VERSION_MAJOR}.${PAHOLE_VERSION_MINOR})
endif

ifneq (${PAHOLE_VERSION},${PAHOLE_VERSION_MAJOR}.${PAHOLE_VERSION_MINOR})
  $(error FATAL: parse ${PAHOLE} version failed, ${PAHOLE_VERSION} != ${PAHOLE_VERSION_MAJOR}.${PAHOLE_VERSION_MINOR})
endif

# see linux:scripts/pahole-version.sh,scripts/Makefile.btf
pahole-ver := $(shell ${PAHOLE} --version | sed -E 's/v([0-9]+)\.([0-9]+)/\1\2/')
ifdef DEBUG
  $(info pahole-ver = ${pahole-ver})
endif

# https://git.kernel.org/pub/scm/devel/pahole/pahole.git use dwarves cmake macros
DWARVES_MAJOR_VERSION := ${PAHOLE_VERSION_MAJOR}
DWARVES_MINOR_VERSION := ${PAHOLE_VERSION_MINOR}

pahole-cflags += -DPAHOLE_VERSION_MAJOR=${PAHOLE_VERSION_MAJOR}
pahole-cflags += -DPAHOLE_VERSION_MINOR=${PAHOLE_VERSION_MINOR}

PAHOLE_VERSION_CODE := $(call version3_code1688,${PAHOLE_VERSION_MAJOR},${PAHOLE_VERSION_MINOR},0)

define pahole_gt
$(call version3_code1688_cmp,${PAHOLE_VERSION_CODE},-gt,${1},${2},0)
endef
define pahole_ge
$(call version3_code1688_cmp,${PAHOLE_VERSION_CODE},-ge,${1},${2},0)
endef
define pahole_eq
$(call version3_code1688_cmp,${PAHOLE_VERSION_CODE},-eq,${1},${2},0)
endef
define pahole_lt
$(call version3_code1688_cmp,${PAHOLE_VERSION_CODE},-lt,${1},${2},0)
endef
define pahole_le
$(call version3_code1688_cmp,${PAHOLE_VERSION_CODE},-le,${1},${2},0)
endef

ifdef DEBUG
  $(info PAHOLE = ${PAHOLE})
  $(info HAVE_PAHOLE = ${HAVE_PAHOLE})
  $(info PAHOLE_VERSION_MAJOR = ${PAHOLE_VERSION_MAJOR})
  $(info PAHOLE_VERSION_MINOR = ${PAHOLE_VERSION_MINOR})
  $(info DWARVES_MAJOR_VERSION = ${DWARVES_MAJOR_VERSION})
  $(info DWARVES_MINOR_VERSION = ${DWARVES_MINOR_VERSION})
  $(info pahole-cflags = ${pahole-cflags})
endif

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

export PAHOLE PAHOLE_VERSION_MAJOR PAHOLE_VERSION_MINOR
export DWARVES_MAJOR_VERSION DWARVES_MINOR_VERSION
export pahole-cflags

endif # end of pahole is found
endif # end of _PAHOLE_MK
