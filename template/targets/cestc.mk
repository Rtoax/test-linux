# SPDX-License-Identifier: GPL-3.0
_TARGET_CESTC = 1

include ${TEMPLATE_DIR}/../hpc/cestc/luca.mk

cflags-lscc-devbin := -device-bin
cflags-lscc-fatbin := -fatbin

CFLAGS_LSCC += -DHAVE_LUCA=1
CFLAGS_LSCC += -D__USE_LUCA__=1

ifneq ($(wildcard ${LUCA_CU_BRIDGE}),)
  CFLAGS_LSCC += -I${LUCA_CU_BRIDGE} -DLUCA_CU_BRIDGE=1
endif

ifneq ($(LUCA_VERSION_MAJOR}),)
  CFLAGS_LSCC += -DLUCA_VERSION_MAJOR=${LUCA_VERSION_MAJOR}
  CFLAGS_LSCC += -DLUCA_VERSION_MINOR=${LUCA_VERSION_MINOR}
  CFLAGS_LSCC += -DLUCA_VERSION_PATCH=${LUCA_VERSION_PATCH}
endif

# FIXME: In file included from sparse.luca:6:
# In file included from /opt/luca/include/hcsparse/hcsparse.h:9:
# /opt/luca/include/hcsparse/interface/hcsp_conversion.h:8:10: fatal error: 'common/hcsp_types.h' file not found
# #include "common/hcsp_types.h"
#          ^~~~~~~~~~~~~~~~~~~~~
CFLAGS_LSCC += -I/opt/luca/include/hcsparse/

# TODO: prefix 'hc' will be renamed.
LDFLAGS_LSCC += -lhccl
LDFLAGS_LSCC += -lhcblas -lhcblasLt
LDFLAGS_LSCC += -lhcfft
LDFLAGS_LSCC += -lhcrand
LDFLAGS_LSCC += -lhcsparse

ifdef ERROR
  CFLAGS_LSCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_LSCC += -DDEBUG=${DEBUG}

  ifneq ($(targets-lscc),)
    $(info CFLAGS_LSCC = ${CFLAGS_LSCC})
    $(info LDFLAGS_LSCC = ${LDFLAGS_LSCC})
  endif
endif

${OUTPUT}%.E.luca: %.luca | ${OUTPUT}
	$(call log_tgt_obj,LSCC E,$(<),$(@))
	${Q}$(LSCC) -E -o $(@) -c $(<) $(CFLAGS_LSCC) $(CFLAGS_LSCC_$(*))

${OUTPUT}%.luca.o: %.luca | ${OUTPUT}
	$(call log_tgt_obj,LSCC,$(<),$(@))
	${Q}$(LSCC) -o $(@) -c $(<) $(CFLAGS_LSCC) $(CFLAGS_LSCC_$(*))

${OUTPUT}%.luca.devbin: %.luca | ${OUTPUT}
	$(call log_tgt_obj,DEVBIN,$(<),$(@))
	${Q}$(LSCC) -o $(@) -c $(<) $(cflags-lscc-devbin) $(CFLAGS_LSCC) $(CFLAGS_LSCC_$(*))

${OUTPUT}%.luca.fatbin: %.luca | ${OUTPUT}
	$(call log_tgt_obj,FATBIN,$(<),$(@))
	${Q}$(LSCC) -o $(@) -c $(<) $(cflags-lscc-fatbin) $(CFLAGS_LSCC) $(CFLAGS_LSCC_$(*))

# Example format of hc_fatbin and hcFatBinSegment, see:
# commit 798dd703bcc9 ("targets/metax.mk: add .hc_fatbin and .hcFatBinSegment targets")
# TODO: section name .hc_fatbin will be renamed.
${OUTPUT}%.luca.hc_fatbin: % | ${OUTPUT}
	$(call log_tgt_obj,HC FATBIN,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hc_fatbin $(<) $(@)

# TODO: section name .hcFatBinSegment will be renamed.
${OUTPUT}%.luca.hcFatBinSegment: % | ${OUTPUT}
	$(call log_tgt_obj,HC FATBIN SEG,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hcFatBinSegment $(<) $(@)

$(targets-lscc): %:
	$(call log_tgt_exe,LSCC LD,$(<),$(@))
	${Q}$(LSCC) -o $(@) $(^) $(LDFLAGS_LSCC) $(LDFLAGS_LSCC_$(*))
