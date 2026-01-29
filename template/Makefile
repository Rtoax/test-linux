# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
# Test all template mk
#
__IGNORE_NOTFOUND_ERROR__ = 1

MAKES := $(shell find -name '*.mk')
MAKES := $(filter-out ./targets/%,${MAKES})
MAKES := $(filter-out ./main.mk,${MAKES})

$(info MAKES = ${MAKES})

define include_stat
  start_$(1)_ms := $(shell date +%s%6N | awk '{print int($$1 / 1000)}')
  include $(1)
  end_$(1)_ms := $(shell date +%s%6N | awk '{print int($$1 / 1000)}')
  cost_$(1)_ms := $(shell echo $(end_$(1)_ms) - $(start_$(1)_ms) | bc)
  $(info Including $(1) cost $(cost_$(1)_ms) ms)
endef

# include each mk for twice to test ifndef-endif pair
#$(foreach mk, ${MAKES} ${MAKES}, $(info Including ${mk}) $(eval include ${mk}))
$(foreach mk, ${MAKES} ${MAKES}, $(eval $(call include_stat,${mk})))

target-post-y := git
target-post-y += logo

include main.mk

git:
	$(call git_config)
	$(call git_archive)
	$(call git_clean,Y)

logo:
	$(call logo_bpf_summit_2021)
	$(call logo_bpf_summit_2021_nocolor)
	$(call logo_gnu,*** )
	$(call logo_linux_tux,*** )
	$(call logo_test_linux,*** )
	$(call logo_tux,*** )
	$(call success,*** )
	$(call wow,*** )
