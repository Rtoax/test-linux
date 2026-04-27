# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# https://git.kernel.org/pub/scm/devel/pahole/pahole.git
#
# Output definitions:
# - HAVE_PAHOLE=[y|n]
# - PAHOLE=
# - PAHOLE_MAJOR=DWARVES_MAJOR=
# - PAHOLE_MINOR=DWARVES_MINOR=
# - pahole-cflags=
#
# Funtions:
# - pahole_{gt,ge,eq,lt,le}()=[y|n]
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
PAHOLE_MAJOR := 0
PAHOLE_MINOR := 0
DWARVES_MAJOR := 0
DWARVES_MINOR := 0

paholeversh = ${TOPDIR}/scripts/version/pahole.sh

PAHOLE_VERSION := $(shell ${paholeversh})
PAHOLE_MAJOR := $(shell ${paholeversh} --major)
PAHOLE_MINOR := $(shell ${paholeversh} --minor)

ifdef DEBUG
  $(info ${PAHOLE} version ${PAHOLE_MAJOR}.${PAHOLE_MINOR})
endif

ifneq (${PAHOLE_VERSION},${PAHOLE_MAJOR}.${PAHOLE_MINOR})
  $(error FATAL: parse ${PAHOLE} version failed, ${PAHOLE_VERSION} != ${PAHOLE_MAJOR}.${PAHOLE_MINOR})
endif

# see linux:scripts/pahole-version.sh,scripts/Makefile.btf
pahole-ver := $(shell ${PAHOLE} --version | sed -E 's/v([0-9]+)\.([0-9]+)/\1\2/')
ifdef DEBUG
  $(info pahole-ver = ${pahole-ver})
endif

# https://git.kernel.org/pub/scm/devel/pahole/pahole.git use dwarves cmake macros
DWARVES_MAJOR := ${PAHOLE_MAJOR}
DWARVES_MINOR := ${PAHOLE_MINOR}

pahole-cflags += -DPAHOLE_MAJOR=${PAHOLE_MAJOR}
pahole-cflags += -DPAHOLE_MINOR=${PAHOLE_MINOR}

$(eval $(call define_version,pahole,version2_code1616,${PAHOLE_MAJOR},${PAHOLE_MINOR}))

ifdef DEBUG
  $(info PAHOLE = ${PAHOLE})
  $(info HAVE_PAHOLE = ${HAVE_PAHOLE})
  $(info PAHOLE_MAJOR = ${PAHOLE_MAJOR})
  $(info PAHOLE_MINOR = ${PAHOLE_MINOR})
  $(info DWARVES_MAJOR = ${DWARVES_MAJOR})
  $(info DWARVES_MINOR = ${DWARVES_MINOR})
  $(info pahole-cflags = ${pahole-cflags})
endif

# The newest pahole is v1.31 right now.
ifneq ($(call pahole_lt,1,32),y)
  $(error "Call pahole_lt failed, $(call pahole_lt,1,32)")
endif

export PAHOLE PAHOLE_MAJOR PAHOLE_MINOR
export DWARVES_MAJOR DWARVES_MINOR
export pahole-cflags

endif # end of pahole is found
endif # end of _PAHOLE_MK
