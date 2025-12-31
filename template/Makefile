# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
# Test all template mk
#
__IGNORE_NOTFOUND_ERROR__ = 1

MAKES := $(shell find -name '*.mk')
MAKES := $(filter-out ./targets/%,${MAKES})
MAKES := $(filter-out ./main.mk,${MAKES})

$(info MAKES = ${MAKES})

$(foreach mk, ${MAKES}, $(eval include ${mk}))

include main.mk
