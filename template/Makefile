# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
# Test all template mk
#
# Usage: $ make MK=[os.mk] DEBUG=1
#
OUTPUT := .output/

V ?= 1

ifdef MK
  MK_ALL := ${MK}
  NOSUBDIR := 1
  DEBUG := 1
else
  MK_ALL := $(shell find -name '*.mk')
endif

MK_TGT := $(filter ./targets/%,${MK_ALL})
MK_TGT := $(filter-out ./targets/test/%,${MK_TGT})

MK_TST := $(filter-out ./targets/%,${MK_ALL})
MK_TST := $(filter-out ./main.mk,${MK_TST})

$(info MK_ALL = ${MK_ALL})
$(info MK_TGT = ${MK_TGT})
$(info MK_TST = ${MK_TST})

include make.mk

# include each mk for twice to test ifndef-endif pair
$(foreach mk, ${MK_TST} ${MK_TST}, $(eval $(call include_stat,${mk})))

subdir-y := targets/test/

target-prep-y += log
target-prep-y += logo

# __main__
$(call include_stat,main.mk)

$(foreach mk, ${MK_TGT}, $(eval $(call include_stat,${mk})))

.PHONY: log
log:
	$(call log_info,Test log_info)

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
