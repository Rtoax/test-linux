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
  $(eval _mk := $(1))
  $(eval _mk_id := $(subst /,_,$(subst .,_,$(1))))
  $(eval _start_$(_mk_id) := $(shell date +%s%6N))
  $(eval include $(_mk))
  $(eval _end_$(_mk_id) := $(shell date +%s%6N))
  $(eval _cost_$(_mk_id) := $(shell echo "scale=3; ($(_end_$(_mk_id)) - $(_start_$(_mk_id))) / 1000" | bc))
  $(info Including $(_mk) -> Done. Took $(_cost_$(_mk_id)) ms)
endef

# include each mk for twice to test ifndef-endif pair
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
