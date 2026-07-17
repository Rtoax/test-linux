# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# https://git.kernel.org/pub/scm/fs/ext2/e2fsprogs.git
#
# Definitions:
#
ifndef _FS_E2FSPROGS_MK
_FS_E2FSPROGS_MK = 1

include define.mk

EXT2FS_H := /usr/include/ext2fs/ext2fs.h

$(call check_file_and_def,${EXT2FS_H},HAVE_EXT2FS_H)

ifdef DEBUG
  $(info EXT2FS_H = ${EXT2FS_H})
endif

endif
