# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - RUNPROG=..../scripts/runprog.sh
#
ifndef _RUNPROG_MK
export _RUNPROG_MK = 1

include dir.mk

RUNPROG := ${TOPDIR}/scripts/runprog.sh

ifdef DEBUG
  RUNPROG += --verbose
endif

export RUNPROG

endif
