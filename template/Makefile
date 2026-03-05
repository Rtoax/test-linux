# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
# Test all template mk
#
# Usage: $ make MK_ALL=[os.mk] DEBUG=1
#
__IGNORE_NOTFOUND_ERROR__ = 1
OUTPUT := .output/

V ?= 1

ifndef MK_ALL
  MK_ALL := $(shell find -name '*.mk')
endif

MK_TGT := $(filter ./targets/%,${MK_ALL})
MK_TGT := $(filter-out ./targets/test/%,${MK_TGT})

MK_TST := $(filter-out ./targets/%,${MK_ALL})
MK_TST := $(filter-out ./main.mk,${MK_TST})

$(info MK_ALL = ${MK_ALL})
$(info MK_TGT = ${MK_TGT})
$(info MK_TST = ${MK_TST})

# Sometimes including an mk file takes too long, and this function can be
# used to effectively measure the time required to include the mk.
# Arguments:
# $1: file to include
define include_stat
  $(eval _mk := $(1))
  $(eval _mk_id := $(subst /,_,$(subst .,_,$(1))))
  $(eval _start_$(_mk_id) := $(shell date +%s%6N))
  $(eval include $(_mk))
  $(eval _end_$(_mk_id) := $(shell date +%s%6N))
  $(eval _cost_$(_mk_id) := $(shell echo "scale=3; ($(_end_$(_mk_id)) - $(_start_$(_mk_id))) / 1000" | bc))
  $(if ${V},$(info Include $(_mk) -> Done. Took $(_cost_$(_mk_id)) ms))
endef

# include each mk for twice to test ifndef-endif pair
$(foreach mk, ${MK_TST} ${MK_TST}, $(eval $(call include_stat,${mk})))

subdir-y := targets/test/

target-prep-y := gitprep
target-prep-y += log
target-prep-y += logo

target-post-y := gitpost

# __main__
$(call include_stat,main.mk)

$(foreach mk, ${MK_TGT}, $(eval $(call include_stat,${mk})))

.PHONY: gitprep
gitprep:
	$(call git_config)
	$(call git_archive)

.PHONY: gitpost
gitpost:
	$(call git_clean,Y)

.PHONY: log
log:
	$(call log_failed,Test log_failed)

.PHONY: logo
logo:
	$(call logo_bpf_summit_2021)
	$(call logo_bpf_summit_2021_nocolor)
	$(call logo_gnu,*** )
	$(call logo_linux_tux,*** )
	$(call logo_test_linux,*** )
	$(call logo_tux,*** )
	$(call success,*** )
	$(call wow,*** )
