# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
# RUNPROG_ARGS=[...]
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
RUNPROG += ${RUNPROG_ARGS}

$(if ${DEBUG}, $(info RUNPROG = ${RUNPROG}))

export RUNPROG

ifneq ($(shell ${RUNPROG} --nolog --nocmdlog -- ls -d ${TOPDIR}),${TOPDIR})
  $(error "ERROR: ${RUNPROG} -- ls -d ${TOPDIR} failed.")
endif

endif
