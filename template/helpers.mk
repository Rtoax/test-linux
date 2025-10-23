# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao
#
# Input definitions:
# - __USE_PROC_HELPERS__
#
# Output definitions:
# - PROC_HELPERS
#
# Append definitions:
# - CFLAGS
# - LDFLAGS
#
_HELPERS = 1

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

define make_helper
@make --no-print-directory --silent -C ${1} ${2}
endef

ifdef __USE_PROC_HELPERS__
  CFLAGS += -I${TOPDIR}/fs/procfs/
  LDFLAGS += -Wl,-rpath,${TOPDIR}/fs/procfs/

  PROC_HELPERS := ${TOPDIR}/fs/procfs/libproc_helpers.so

  ${PROC_HELPERS}:
	$(call make_helper,${TOPDIR}/fs/procfs/,libproc_helpers.so)
endif

ifdef DEBUG
  $(info PROC_HELPERS = ${PROC_HELPERS})
endif
