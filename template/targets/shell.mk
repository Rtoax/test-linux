# SPDX-License-Identifier: GPL-3.0
_TARGET_SHELL = 1

SHELL ?= bash

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

RUN_SHELL := ${TOPDIR}/template/targets/run_prog.sh

ifdef DEBUG
  RUN_SHELL += --verbose
endif

%.sh.log: %.sh
	$(call log_tgt_exe,SHELL,$(<),$(@))
	$(Q)$(RUN_SHELL) $(@) ${SHELL} $(<) $(ARGS_$(*)) $(SHELL_ARGS_$(<))
