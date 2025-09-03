# SPDX-License-Identifier: GPL-3.0
# https://www.metax-tech.com/
_TARGET_METAX = 1

MXCC := $(shell which mxcc 2>/dev/null)
HTCC := $(shell which htcc 2>/dev/null)

HPCC_REALPATH := $(shell readlink /opt/hpcc 2>/dev/null || true)
HPCC_CU_BRIDGE := /opt/hpcc/tools/cu-bridge/include/

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

CFLAGS_HTCC_DEVBIN := -device-bin
CFLAGS_HTCC_FATBIN := -fatbin

ifneq ($(wildcard ${HPCC_CU_BRIDGE}),)
  CFLAGS_HTCC += -I${HPCC_CU_BRIDGE} -DHPCC_CU_BRIDGE=1
endif

ifneq ($(wildcard ${HPCC_REALPATH}),)
  GREP := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'
  HPCC_VERSION_RAW := $(shell echo ${HPCC_REALPATH} | ${GREP} | head -1)
  HPCC_VERSION_MAJOR := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$1}')
  HPCC_VERSION_MINOR := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$2}')
  HPCC_VERSION_PATCH := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$3}')
  CFLAGS_HTCC += -DHPCC_VERSION_MAJOR=${HPCC_VERSION_MAJOR}
  CFLAGS_HTCC += -DHPCC_VERSION_MINOR=${HPCC_VERSION_MINOR}
  CFLAGS_HTCC += -DHPCC_VERSION_PATCH=${HPCC_VERSION_PATCH}
endif

ifdef ERROR
  CFLAGS_MXCC += -DERROR=1
  CFLAGS_HTCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_MXCC += -DDEBUG=${DEBUG}
  CFLAGS_HTCC += -DDEBUG=${DEBUG}

  ifneq ($(targets-mxcc),)
    $(info $(shell ${MXCC} --version))
    $(info MXCC = ${MXCC})
    $(info CFLAGS_MXCC = ${CFLAGS_MXCC})
    $(info LDFLAGS_MXCC = ${LDFLAGS_MXCC})
  endif
  ifneq ($(targets-htcc),)
    $(info $(shell ${HTCC} --version))
    $(info HTCC = ${HTCC})
    $(info CFLAGS_HTCC = ${CFLAGS_HTCC})
    $(info LDFLAGS_HTCC = ${LDFLAGS_HTCC})
    $(info HPCC_VERSION_RAW = ${HPCC_VERSION_RAW})
    $(info HPCC_VERSION_MAJOR = ${HPCC_VERSION_MAJOR})
    $(info HPCC_VERSION_MINOR = ${HPCC_VERSION_MINOR})
    $(info HPCC_VERSION_PATCH = ${HPCC_VERSION_PATCH})
  endif
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

${OUTPUT}%.devbin: %.hpcc | ${OUTPUT}
	$(call log_tgt_obj,DEVBIN,$(<),$(@))
	${Q}$(HTCC) -o $(@) -c $(<) $(CFLAGS_HTCC_DEVBIN) $(CFLAGS_HTCC) $(CFLAGS_HTCC_$(*))

${OUTPUT}%.fatbin: %.hpcc | ${OUTPUT}
	$(call log_tgt_obj,FATBIN,$(<),$(@))
	${Q}$(HTCC) -o $(@) -c $(<) $(CFLAGS_HTCC_FATBIN) $(CFLAGS_HTCC) $(CFLAGS_HTCC_$(*))

$(targets-htcc): %:
	$(call log_tgt_exe,HTCC LD,$(<),$(@))
	${Q}$(HTCC) -o $(@) $(^) $(LDFLAGS_HTCC) $(LDFLAGS_HTCC_$(*))
