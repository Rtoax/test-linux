# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Definitions:
# - HAVE_MKFS_XFS=[y|n]
#
ifndef _FS_XFSPROGS_MK
_FS_XFSPROGS_MK = 1

include define.mk

$(call find_cmd_and_def,mkfs.xfs)

ifneq (${HAVE_MKFS_XFS},y)
  $(warning Not found mkfs.xfs, please install 'xfsprogs' first)
else
  export HAVE_XFSPROGS := y
endif

ifdef DEBUG
  $(info HAVE_XFSPROGS = ${HAVE_XFSPROGS})
endif

endif
