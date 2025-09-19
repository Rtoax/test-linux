# SPDX-License-Identifier: GPL-3.0
_TARGET_AMD = 1

include ${TEMPLATE_DIR}/../hpc/amd/rocm/rocm.mk

CFLAGS_HIPCC += -DHAVE_HIP=1

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

$(targets-hipcc): %:
	$(call log_tgt_exe,HIPCC LD,$(<),$(@))
	${Q}$(HIPCC) -o $(@) $(^) $(LDFLAGS_HIPCC) $(LDFLAGS_HIPCC_$(*))
