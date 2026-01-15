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
	$(call logo_bpf_summit_2021)
	$(call logo_bpf_summit_2021_nocolor)
	$(call logo_gnu,*** )
	$(call logo_linux_tux,*** )
	$(call logo_test_linux,*** )
	$(call logo_tux,*** )
	$(call success,*** )
	$(call wow,*** )
