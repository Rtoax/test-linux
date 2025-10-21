# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao

_TARGET_AMD = 1

include ${TEMPLATE_DIR}/../hpc/amd/rocm/rocm.mk

CFLAGS_HIPCC += -DHAVE_HIP=1
CFLAGS_HIPCC += -D__USE_HIP__=1
ifdef HAVE_RCCL
  CFLAGS_HIPCC += -DHAVE_RCCL=1
endif

ifneq ($(HIPCONFIG),)
  CFLAGS_HIPCC += $(shell ${HIPCONFIG} --cpp_config)
endif

LDFLAGS_HIPCC := -lhipfft
LDFLAGS_HIPCC += -lhipsparse
LDFLAGS_HIPCC += -lhiprand
LDFLAGS_HIPCC += -lhipblas
LDFLAGS_HIPCC += -lhipblaslt
ifdef HAVE_RCCL
  LDFLAGS_HIPCC += -lrccl
endif

ifdef ERROR
  CFLAGS_HIPCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_HIPCC += -DDEBUG=${DEBUG}
  $(info CFLAGS_HIPCC = ${CFLAGS_HIPCC})
  $(info LDFLAGS_HIPCC = ${LDFLAGS_HIPCC})
endif

${OUTPUT}%.hip.o: %.hip | ${OUTPUT}
	$(call log_tgt_obj,HIPCC,$(<),$(@))
	${Q}$(HIPCC) -o $(@) -c $(<) $(CFLAGS_HIPCC) $(CFLAGS_HIPCC_$(*))

${OUTPUT}%.hip_fatbin: % | ${OUTPUT}
	$(call log_tgt_obj,HIP FATBIN,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hip_fatbin $(<) $(@)

${OUTPUT}%.hipFatBinSegment: % | ${OUTPUT}
	$(call log_tgt_obj,HIP FATBIN SEG,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hipFatBinSegment $(<) $(@)

$(target-hipcc-y): %:
	$(call log_tgt_exe,HIPCC LD,$(<),$(@))
	${Q}$(HIPCC) -o $(@) $(^) $(LDFLAGS_HIPCC) $(LDFLAGS_HIPCC_$(*))
