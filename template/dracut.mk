# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_DRACUT=[y|n]
# - DRACUT_{VERSION,MAJOR,MINOR}=
#
ifndef _DRACUT_MK
_DRACUT_MK = 1

DRACUT := $(shell which dracut 2>/dev/null)

ifeq (${DRACUT},)
  export HAVE_DRACUT := n
else
export HAVE_DRACUT := y
export DRACUT

include dir.mk

dracutversh = ${TOPDIR}/scripts/version/dracut.sh

DRACUT_VERSION := $(shell ${dracutversh})
DRACUT_MAJOR := $(shell ${dracutversh} --major)
DRACUT_MINOR := $(shell ${dracutversh} --minor)

ifdef DEBUG
  $(info HAVE_DRACUT = ${HAVE_DRACUT})
  $(info DRACUT_VERSION ${DRACUT_VERSION})
  $(info DRACUT_MAJOR ${DRACUT_MAJOR})
  $(info DRACUT_MINOR ${DRACUT_MINOR})
endif

ifneq (${DRACUT_VERSION},${DRACUT_MAJOR}-${DRACUT_MINOR})
  $(error ${DRACUT_VERSION} != ${DRACUT_MAJOR}-${DRACUT_MINOR})
endif

export DRACUT_VERSION DRACUT_MAJOR DRACUT_MINOR

endif # end of HAVE_DRACUT

endif
