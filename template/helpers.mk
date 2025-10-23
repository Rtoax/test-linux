# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao
#
# Input definitions:
# - __USE_PROC_HELPERS__
#
_HELPERS = 1

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

define make_helper
@make -C ${1} ${2} >/dev/null
endef

ifdef __USE_PROC_HELPERS__
  unused := $(call make_helper,${TOPDIR}/fs/procfs/,libproc_helpers.so)
  CFLAGS += -I${TOPDIR}/fs/procfs/
  LDFLAGS += -Wl,-rpath,${TOPDIR}/fs/procfs/
endif

PROC_HELPERS := ${TOPDIR}/fs/procfs/libproc_helpers.so

ifdef DEBUG
  $(info PROC_HELPERS = ${PROC_HELPERS})
endif
