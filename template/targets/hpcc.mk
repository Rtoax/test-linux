# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# This makefile use to compile MetaX targets.
#
# https://www.metax-tech.com/
#
# Targets list:
# - .maca.o
# - .E.hpcc
# - .hpcc.o
# - .hpcc.so.o
# - .hpcc.a.o
# - .hpcc.devbin
# - .hpcc.fatbin
# - .hpcc.hc_fatbin
# - .hpcc.hcFatBinSegment
# - target-htcc-y
# - target-htcc-libso-y
#
# Input definitions:
# - HPCC_ROOT
# - NODEFAULTRPATH
#
ifndef _TARGET_HPCC_MK
_TARGET_HPCC_MK = 1

include bits/targets.mk
include metax/hpcc.mk
include cflags.mk
include dir.mk
include string.mk

cflags-htcc-devbin := -device-bin
cflags-htcc-fatbin := -fatbin
cflags-htcc-so := -Xcompiler -fPIC
ldflags-htcc-so := -shared -Xcompiler -fPIC


CFLAGS_HTCC += -I${TOPDIR}/libs/
CFLAGS_HTCC += -I${TOPDIR}/hpc/nvidia/cuda/
CFLAGS_HTCC += -I${TOPDIR}/hpc/nvidia/cuda/adapter/include/
CFLAGS_HTCC += -DHAVE_HPCC=1
CFLAGS_HTCC += -D__USE_HPCC__=1

ifneq ($(wildcard ${HPCC_CU_BRIDGE}),)
  CFLAGS_HTCC += -I${HPCC_CU_BRIDGE} -DHPCC_CU_BRIDGE=1
endif
ifdef HAVE_HCDNN
  CFLAGS_HTCC += -DHAVE_HCDNN=1
endif

ifneq ($(HPCC_MAJOR}),)
  CFLAGS_HTCC += -DHPCC_MAJOR=${HPCC_MAJOR}
  CFLAGS_HTCC += -DHPCC_MINOR=${HPCC_MINOR}
  CFLAGS_HTCC += -DHPCC_PATCH=${HPCC_PATCH}
endif

# FIXME: In file included from sparse.hpcc:6:
# In file included from /opt/hpcc/include/hcsparse/hcsparse.h:9:
# /opt/hpcc/include/hcsparse/interface/hcsp_conversion.h:8:10: fatal error: 'common/hcsp_types.h' file not found
# #include "common/hcsp_types.h"
#          ^~~~~~~~~~~~~~~~~~~~~
CFLAGS_HTCC += -I${HPCC_ROOT}/include/hcsparse/
CFLAGS_HTCC += -I${HPCC_ROOT}/include/hcblas/

# FIXME: warning: 'visibility' attribute ignored
CFLAGS_HTCC += -Wno-ignored-attributes

LDFLAGS_HTCC += -lhccl
LDFLAGS_HTCC += -lhcblas -lhcblasLt
LDFLAGS_HTCC += -lhcfft
LDFLAGS_HTCC += -lhcrand
LDFLAGS_HTCC += -lhcsparse
LDFLAGS_HTCC += -lhcsolver
LDFLAGS_HTCC += -lhcfile

ifdef NODEFAULTRPATH
  # Remove default so search directory, see ldflags: -Wl,-rpath,/path/to/so/
  LDFLAGS_HTCC += -nodefaultrpath
endif

ifdef ERROR
  CFLAGS_HTCC += -DERROR=1
endif
ifdef DEBUG
  CFLAGS_HTCC += -DDEBUG=${DEBUG}
endif

CFLAGS_HTCC_SO += ${CFLAGS_HTCC}
CFLAGS_HTCC_SO += ${cflags-htcc-so}
LDFLAGS_HTCC_SO += ${LDFLAGS_HTCC}
LDFLAGS_HTCC_SO += ${ldflags-htcc-so}

CFLAGS_HTCC_A += ${CFLAGS_HTCC_SO}

ifdef DEBUG
  ifneq ($(target-htcc-y),)
    $(info CFLAGS_HTCC = ${CFLAGS_HTCC})
    $(info LDFLAGS_HTCC = ${LDFLAGS_HTCC})
  endif
endif

# MetaX HPCC support .cu and .hpcc suffix
# $1 - suffix of file: hpcc, cu
define hpcc_obj
$${OUTPUT}%.E.hpcc: %.${1} | $${OUTPUT}
	@$(call log_obj,${HTCC} E,$$(@))
	$${Q}$$(HTCC) -E -o $$(@) -c $$(<) $$(CFLAGS_HTCC) $$(CFLAGS_HTCC_$$(*))

$${OUTPUT}%.hpcc.o: %.${1} | $${OUTPUT}
	@$(call log_obj,${HTCC},$$(@))
	$${Q}$$(HTCC) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CFLAGS_HTCC) $$(CFLAGS_HTCC_$$(*))

$${OUTPUT}%.hpcc.devbin: %.${1} | $${OUTPUT}
	@$(call log_obj,${HTCC} DEVBIN,$$(@))
	$${Q}$$(HTCC) -o $$(@) -c $$(<) $$(cflags-htcc-devbin) $$(CFLAGS_HTCC) $$(CFLAGS_HTCC_$$(*))

$${OUTPUT}%.hpcc.fatbin: %.${1} | $${OUTPUT}
	@$(call log_obj,${HTCC} FATBIN,$$(@))
	$${Q}$$(HTCC) -o $$(@) -c $$(<) $$(cflags-htcc-fatbin) $$(CFLAGS_HTCC) $$(CFLAGS_HTCC_$$(*))
endef
# $1 - suffix of file: hpcc, cu
define hpcc_obj_so
$${OUTPUT}%.hpcc.so.o: %.${1} | $${OUTPUT}
	@$(call log_obj,${HTCC} CC SO,$$(@))
	$${Q}$$(HTCC) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CFLAGS_HTCC_SO) $$(CFLAGS_HTCC_SO_$$(*))
endef
# $1 - suffix of file: hpcc, cu
define hpcc_obj_a
$${OUTPUT}%.hpcc.a.o: %.${1} | $${OUTPUT}
	@$(call log_obj,${HTCC} CC A,$$(@))
	$${Q}$$(HTCC) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CFLAGS_HTCC_A) $$(CFLAGS_HTCC_A_$$(*))
endef
$(eval $(call hpcc_obj,cu))
$(eval $(call hpcc_obj,hpcc))
$(eval $(call hpcc_obj_so,cu))
$(eval $(call hpcc_obj_so,hpcc))
$(eval $(call hpcc_obj_a,cu))
$(eval $(call hpcc_obj_a,hpcc))

# Example format of hc_fatbin and hcFatBinSegment, see:
# commit 798dd703bcc9 ("targets/hpcc.mk: add .hc_fatbin and .hcFatBinSegment targets")
${OUTPUT}%.hpcc.hc_fatbin: % | ${OUTPUT}
	@$(call log_obj,${OBJCOPY} FATBIN,$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hc_fatbin $(<) $(@)

${OUTPUT}%.hpcc.hcFatBinSegment: % | ${OUTPUT}
	@$(call log_obj,${OBJCOPY} FATBIN SEG,$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hcFatBinSegment $(<) $(@)

$(target-htcc-y): %:
	@$(call log_tgt,${HTCC} LD,$(@))
	${Q}$(HTCC) -o $(@) $(^) $(LDFLAGS_HTCC) $(LDFLAGS_HTCC_$(*))

$(target-htcc-libso-y): %:
	@$(call log_tgt,${HTCC} SO,$(@))
	${Q}$(HTCC) -o $(@) $(^) $(LDFLAGS_HTCC_SO) $(LDFLAGS_HTCC_SO$(*))

$(call target_objects_append_output_prefix,${target-htcc-libso-y})
$(call add_library_objects,${target-htcc-libso-y})
$(call add_library_depends,${target-htcc-libso-y},.d)

$(call target_objects_append_output_prefix,${target-htcc-y})
$(call add_target_objects,.cu,.hpcc.o,${target-htcc-y},${HPCC_HELPERS})
$(call add_target_depends,${target-htcc-y},.hpcc.o.d,.d)

endif
