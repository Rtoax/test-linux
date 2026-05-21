# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - RUNPROG=[/path/to/runprog.sh [args...]]
#
ifndef _RUNPROG_MK
_RUNPROG_MK = 1

include dir.mk

RUNPROG := ${TOPDIR}/scripts/runprog.sh

$(if ${DEBUG}, $(eval RUNPROG += --verbose))
$(if ${TMOUT}, $(eval RUNPROG += --timeout ${TMOUT}))

$(if ${DEBUG}, $(info RUNPROG = ${RUNPROG}))

export RUNPROG

endif
