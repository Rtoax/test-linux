# SPDX-License-Identifier: GPL-3.0
# https://www.metax-tech.com/

MXCC := $(shell which mxcc 2>/dev/null)
MXLD := ??

HPCC_232 := /opt/hpcc-2.32.0/htgpu_llvm/bin/

ifeq ($(MXCC),)
  ifneq ($(wildcard ${HPCC_232}),)
    MXCC := ${HPCC_232}/htcc
    MXLD := ${HPCC_232}/ld.lld
  endif
endif

ifeq ($(MXCC),)
  $(error Not found mxcc, install MetaX Toolkit first)
endif
ifeq ($(MXLD),)
  MXLD := MXCC
endif

ifdef DEBUG
  $(info MXCC = ${MXCC})
  $(info MXLD = ${MXLD})
endif

%.maca.o: %.maca
	$(call log_tgt_obj,MXCC,$(<),$(@))
	${Q}$(MXCC) -o $(@) -c $(<) $(CFLAGS_MXCC) $(CFLAGS_MXCC_$(*))

$(TARGETS_MXCC): %:
	$(call log_tgt_exe,MXCC LD,$(<),$(@))
	${Q}$(MXLD) -o $(@) $(^) $(LDFLAGS_MXCC) $(LDFLAGS_MXCC_$(*))
