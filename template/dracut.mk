# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_DRACUT=[y|n]
# - DRACUT=[/usr/bin/dracut]
# - DRACUT_{VERSION,MAJOR,MINOR}=
#
ifndef _DRACUT_MK
_DRACUT_MK = 1

include define.mk

$(call find_cmd_and_def,dracut)

ifneq (${DRACUT},)
include dir.mk

dracutversh = ${TOPDIR}/scripts/version/dracut.sh

DRACUT_VERSION := $(shell ${dracutversh})
DRACUT_MAJOR := $(shell ${dracutversh} --major)
DRACUT_MINOR := $(shell ${dracutversh} --minor)

export DRACUT_VERSION DRACUT_MAJOR DRACUT_MINOR

ifneq (${DRACUT_VERSION},${DRACUT_MAJOR}-${DRACUT_MINOR})
  $(error dracut version error: ${DRACUT_VERSION} != ${DRACUT_MAJOR}-${DRACUT_MINOR})
endif

endif # end of HAVE_DRACUT

ifdef DEBUG
  $(info DRACUT_VERSION ${DRACUT_VERSION})
  $(info DRACUT_MAJOR ${DRACUT_MAJOR})
  $(info DRACUT_MINOR ${DRACUT_MINOR})
endif

endif
