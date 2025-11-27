# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Targets list:
# %.hip.o
# %.hip_fatbin
# %.hipFatBinSegment
# target-hipcc-y
# target-hipcc-libso-y
# target-hipcc-liba-y
#
# Input definitions:
# - HAVE_HIPSOLVER=
# - HAVE_RCCL=
# - CFLAGS_HIPCC=
# - CFLAGS_HIPCC_SO=
# - CFLAGS_HIPCC_A=
# - LDFLAGS_HIPCC=
# - LDFLAGS_HIPCC_SO=

_TARGET_AMD = 1

include rocm.mk

cflags-hipcc-so := -Xcompiler -fPIC
ldflags-hipcc-so := -shared -Xcompiler -fPIC

CFLAGS_HIPCC += -DHAVE_HIP=1
CFLAGS_HIPCC += -D__USE_HIP__=1
ifdef HAVE_HIPSOLVER
  CFLAGS_HIPCC += -DHAVE_HIPSOLVER=1
endif
ifdef HAVE_HIPBLASLT
  CFLAGS_HIPCC += -DHAVE_HIPBLASLT=1
endif
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
LDFLAGS_HIPCC += -lhipsolver
ifdef HAVE_RCCL
  LDFLAGS_HIPCC += -lrccl
endif

ifdef ERROR
  CFLAGS_HIPCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_HIPCC += -DDEBUG=${DEBUG}
endif

CFLAGS_HIPCC_SO += ${CFLAGS_HIPCC}
CFLAGS_HIPCC_SO += ${cflags-hipcc-so}
LDFLAGS_HIPCC_SO += ${LDFLAGS_HIPCC}
LDFLAGS_HIPCC_SO += ${ldflags-hipcc-so}

CFLAGS_HIPCC_A += ${CFLAGS_HIPCC_SO}

ifdef DEBUG
  $(info CFLAGS_HIPCC = ${CFLAGS_HIPCC})
  $(info CFLAGS_HIPCC_SO = ${CFLAGS_HIPCC_SO})
  $(info LDFLAGS_HIPCC = ${LDFLAGS_HIPCC})
endif

# AMD ROCm HIP support .cu and .hip suffix.
# $1 - suffix of file: hip, cu
define hip_obj
$${OUTPUT}%.hip.o: %.${1} | $${OUTPUT}
	$(call log_obj,HIPCC,$$(<),$$(@))
	$${Q}$$(HIPCC) -o $$(@) -c $$(<) $$(CFLAGS_HIPCC) $$(CFLAGS_HIPCC_$$(*))
endef
# $1 - suffix of file: hip, cu
define hip_obj_so
$${OUTPUT}%.hip.so.o: %.${1} | $${OUTPUT}
	$(call log_obj,HIPCC SO,$$(<),$$(@))
	$${Q}$$(HIPCC) -o $$(@) -c $$(<) $$(CFLAGS_HIPCC_SO) $$(CFLAGS_HIPCC_SO_$$(*))
endef
# $1 - suffix of file: hip, cu
define hip_obj_a
$${OUTPUT}%.hip.a.o: %.${1} | $${OUTPUT}
	$(call log_obj,HIPCC A,$$(<),$$(@))
	$${Q}$$(HIPCC) -o $$(@) -c $$(<) $$(CFLAGS_HIPCC_A) $$(CFLAGS_HIPCC_A_$$(*))
endef
$(eval $(call hip_obj,cu))
$(eval $(call hip_obj,hip))
$(eval $(call hip_obj_so,cu))
$(eval $(call hip_obj_so,hip))
$(eval $(call hip_obj_a,cu))
$(eval $(call hip_obj_a,hip))

${OUTPUT}%.hip_fatbin: % | ${OUTPUT}
	$(call log_obj,HIP FATBIN,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hip_fatbin $(<) $(@)

${OUTPUT}%.hipFatBinSegment: % | ${OUTPUT}
	$(call log_obj,HIP FATBIN SEG,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hipFatBinSegment $(<) $(@)

$(target-hipcc-y): %:
	$(call log_exe,HIPCC LD,$(<),$(@))
	${Q}$(HIPCC) -o $(@) $(^) $(LDFLAGS_HIPCC) $(LDFLAGS_HIPCC_$(*))

$(target-hipcc-libso-y): %:
	$(call log_exe,HIPCC SO,$(<),$(@))
	${Q}$(HIPCC) -o $(@) $(^) $(LDFLAGS_HIPCC_SO) $(LDFLAGS_HIPCC_SO$(*))

$(target-hipcc-liba-y): %:
	$(call log_exe,HIPCC AR,$(<),$(@))
	${Q}ar rcs $(@) $(^)
