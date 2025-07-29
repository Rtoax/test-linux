# SPDX-License-Identifier: GPL-3.0
# https://www.metax-tech.com/

MXCC := $(shell which mxcc 2>/dev/null)
HTCC := $(shell which htcc 2>/dev/null)

ifeq ($(MXCC),)
  ifneq ($(targets-mxcc),)
    $(error Not found mxcc, install MetaX Toolkit first)
  endif
endif
ifeq ($(HTCC),)
  ifneq ($(targets-htcc),)
    $(error Not found htcc, install MetaX hpcc first)
  endif
endif

ifdef ERROR
  CFLAGS_MXCC += -DERROR=1
  CFLAGS_HTCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_MXCC += -DDEBUG
  CFLAGS_HTCC += -DDEBUG
  $(info MXCC = ${MXCC})
  $(info HTCC = ${HTCC})
  $(info CFLAGS_MXCC = ${CFLAGS_MXCC})
  $(info LDFLAGS_MXCC = ${LDFLAGS_MXCC})
  $(info CFLAGS_HTCC = ${CFLAGS_HTCC})
  $(info LDFLAGS_HTCC = ${LDFLAGS_HTCC})
endif

${OUTPUT}%.maca.o: %.maca | ${OUTPUT}
	$(call log_tgt_obj,MXCC,$(<),$(@))
	${Q}$(MXCC) -o $(@) -c $(<) $(CFLAGS_MXCC) $(CFLAGS_MXCC_$(*))

$(targets-mxcc): %:
	$(call log_tgt_exe,MXCC LD,$(<),$(@))
	${Q}$(MXCC) -o $(@) $(^) $(LDFLAGS_MXCC) $(LDFLAGS_MXCC_$(*))

${OUTPUT}%.E.hpcc: %.hpcc | ${OUTPUT}
	$(call log_tgt_obj,HTCC E,$(<),$(@))
	${Q}$(HTCC) -E -o $(@) -c $(<) $(CFLAGS_HTCC) $(CFLAGS_HTCC_$(*))

${OUTPUT}%.hpcc.o: %.hpcc | ${OUTPUT}
	$(call log_tgt_obj,HTCC,$(<),$(@))
	${Q}$(HTCC) -o $(@) -c $(<) $(CFLAGS_HTCC) $(CFLAGS_HTCC_$(*))

$(targets-htcc): %:
	$(call log_tgt_exe,HTCC LD,$(<),$(@))
	${Q}$(HTCC) -o $(@) $(^) $(LDFLAGS_HTCC) $(LDFLAGS_HTCC_$(*))
