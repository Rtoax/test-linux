# SPDX-License-Identifier: GPL-3.0
# https://www.metax-tech.com/
_TARGET_METAX = 1

include ${TEMPLATE_DIR}/../hpc/metax/hpcc.mk

cflags-htcc-devbin := -device-bin
cflags-htcc-fatbin := -fatbin

CFLAGS_HTCC += -DHAVE_HCCL=1

ifneq ($(wildcard ${HPCC_CU_BRIDGE}),)
  CFLAGS_HTCC += -I${HPCC_CU_BRIDGE} -DHPCC_CU_BRIDGE=1
endif

ifneq ($(HPCC_VERSION_MAJOR}),)
  CFLAGS_HTCC += -DHPCC_VERSION_MAJOR=${HPCC_VERSION_MAJOR}
  CFLAGS_HTCC += -DHPCC_VERSION_MINOR=${HPCC_VERSION_MINOR}
  CFLAGS_HTCC += -DHPCC_VERSION_PATCH=${HPCC_VERSION_PATCH}
endif

# FIXME: In file included from sparse.hpcc:6:
# In file included from /opt/hpcc/include/hcsparse/hcsparse.h:9:
# /opt/hpcc/include/hcsparse/interface/hcsp_conversion.h:8:10: fatal error: 'common/hcsp_types.h' file not found
# #include "common/hcsp_types.h"
#          ^~~~~~~~~~~~~~~~~~~~~
CFLAGS_HTCC += -I/opt/hpcc/include/hcsparse/

LDFLAGS_HTCC += -lhccl
LDFLAGS_HTCC += -lhcblas -lhcblasLt
LDFLAGS_HTCC += -lhcfft
LDFLAGS_HTCC += -lhcrand
LDFLAGS_HTCC += -lhcsparse

ifdef ERROR
  CFLAGS_MXCC += -DERROR=1
  CFLAGS_HTCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_MXCC += -DDEBUG=${DEBUG}
  CFLAGS_HTCC += -DDEBUG=${DEBUG}

  ifneq ($(targets-mxcc),)
    $(info CFLAGS_MXCC = ${CFLAGS_MXCC})
    $(info LDFLAGS_MXCC = ${LDFLAGS_MXCC})
  endif
  ifneq ($(targets-htcc),)
    $(info CFLAGS_HTCC = ${CFLAGS_HTCC})
    $(info LDFLAGS_HTCC = ${LDFLAGS_HTCC})
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
	${Q}$(HTCC) -o $(@) -c $(<) $(cflags-htcc-devbin) $(CFLAGS_HTCC) $(CFLAGS_HTCC_$(*))

${OUTPUT}%.fatbin: %.hpcc | ${OUTPUT}
	$(call log_tgt_obj,FATBIN,$(<),$(@))
	${Q}$(HTCC) -o $(@) -c $(<) $(cflags-htcc-fatbin) $(CFLAGS_HTCC) $(CFLAGS_HTCC_$(*))

# Example format of hc_fatbin and hcFatBinSegment, see:
# commit 798dd703bcc9 ("targets/metax.mk: add .hc_fatbin and .hcFatBinSegment targets")
${OUTPUT}%.hc_fatbin: % | ${OUTPUT}
	$(call log_tgt_obj,HC FATBIN,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hc_fatbin $(<) $(@)

${OUTPUT}%.hcFatBinSegment: % | ${OUTPUT}
	$(call log_tgt_obj,HC FATBIN SEG,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hcFatBinSegment $(<) $(@)

$(targets-htcc): %:
	$(call log_tgt_exe,HTCC LD,$(<),$(@))
	${Q}$(HTCC) -o $(@) $(^) $(LDFLAGS_HTCC) $(LDFLAGS_HTCC_$(*))
