# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Input definitions:
# - RUNPROG_ARGS=[...]
#
# Output definitions:
# - RUNPROG=[/path/to/runprog.sh [args...]]
#
# Functions:
# - __prog_stdout_color()
# - __prog_stdout_rst()
#
ifndef _RUNPROG_MK
_RUNPROG_MK = 1

include dir.mk

RUNPROG := ${TOPDIR}/scripts/runprog.sh

$(if ${DEBUG}, $(eval RUNPROG += --verbose))
$(if ${FORCE}, $(eval RUNPROG += --force))
$(if ${TMOUT}, $(eval RUNPROG += --timeout ${TMOUT}))
RUNPROG += ${RUNPROG_ARGS}

$(if ${DEBUG}, $(info RUNPROG = ${RUNPROG}))

export RUNPROG

ifneq ($(wildcard /usr/bin/tput),)
  # 8 is gray, we could change any ansi type here.
  define __prog_stdout_color
  tput setaf 8
  endef
  define __prog_stdout_rst
  tput sgr0
  endef
else
  define __prog_stdout_color
  endef
  define __prog_stdout_rst
  endef
endif

ifneq ($(shell ${RUNPROG} --nolog --nocmdlog -- ls -d ${TOPDIR}),${TOPDIR})
  $(error "ERROR: ${RUNPROG} -- ls -d ${TOPDIR} failed.")
endif

endif
