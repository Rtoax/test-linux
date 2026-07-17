# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# https://git.kernel.org/pub/scm/fs/ext2/e2fsprogs.git
#
# Definitions:
# - HAVE_E2FSPROGS=[y]
# - HAVE_EXT2FS_H=[y|n]
# - HAVE_MKFS_EXT4=[y|n]
# - HAVE_MKFS_EXT3=[y|n]
#
# - e2fsprogs-cflags=
# - e2fsprogs-ldflags=
#
ifndef _FS_E2FSPROGS_MK
_FS_E2FSPROGS_MK = 1

include define.mk

EXT2FS_H := /usr/include/ext2fs/ext2fs.h

$(call check_file_and_def,${EXT2FS_H},HAVE_EXT2FS_H)
$(call find_cmd_and_def,mkfs.ext3)
$(call find_cmd_and_def,mkfs.ext4)

ifneq (${HAVE_MKFS_EXT4},y)
  $(error Not found mkfs.ext4, please install 'e2fsprogs' first)
endif

export HAVE_E2FSPROGS := y
export e2fsprogs-cflags := $(shell pkg-config --cflags ext2fs)
export e2fsprogs-ldflags := $(shell pkg-config --libs ext2fs)

ifdef DEBUG
  $(info EXT2FS_H = ${EXT2FS_H})
  $(info e2fsprogs-cflags = ${e2fsprogs-cflags})
  $(info e2fsprogs-ldflags = ${e2fsprogs-ldflags})
endif

endif
