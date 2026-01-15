# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
# Test all template mk
#
__IGNORE_NOTFOUND_ERROR__ = 1

MAKES := $(shell find -name '*.mk')
MAKES := $(filter-out ./targets/%,${MAKES})
MAKES := $(filter-out ./main.mk,${MAKES})

$(info MAKES = ${MAKES})

# include each mk for twice to test ifndef-endif pair
$(foreach mk, ${MAKES} ${MAKES}, $(eval include ${mk}))

target-post-y := logo

include main.mk

logo:
	$(call tl_logo1,*** )
	$(call tl_tux_logo1,*** )
	$(call tl_linux_tux_logo1,*** )
