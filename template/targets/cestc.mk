# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Targets list:
# - .E.luca
# - .luca.o
# - .luca.so.o
# - .luca.a.o
# - .luca.devbin
# - .luca.fatbin
# - .luca.hc_fatbin
# - .luca.hcFatBinSegment
# - target-lscc-y
# - target-lscc-libso-y
# - target-lscc-liba-y

_TARGET_CESTC = 1

include luca.mk

cflags-lscc-devbin := -device-bin
cflags-lscc-fatbin := -fatbin
cflags-lscc-so := -Xcompiler -fPIC
ldflags-lscc-so := -shared -Xcompiler -fPIC

CFLAGS_LSCC += -DHAVE_LUCA=1
CFLAGS_LSCC += -D__USE_LUCA__=1

ifneq ($(wildcard ${LUCA_CU_BRIDGE}),)
  CFLAGS_LSCC += -I${LUCA_CU_BRIDGE} -DLUCA_CU_BRIDGE=1
endif
ifdef HAVE_LCDNN
  CFLAGS_LSCC += -DHAVE_LCDNN=1
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
CFLAGS_LSCC += -I/opt/luca/include/hcblas/

# TODO: prefix 'hc' will be renamed.
LDFLAGS_LSCC += -lhccl
LDFLAGS_LSCC += -lhcblas -lhcblasLt
LDFLAGS_LSCC += -lhcfft
LDFLAGS_LSCC += -lhcrand
LDFLAGS_LSCC += -lhcsparse
LDFLAGS_LSCC += -lhcsolver

# Remove default so search directory, see ldflags: -Wl,-rpath,/path/to/so/
LDFLAGS_LSCC := -nodefaultrpath

ifdef ERROR
  CFLAGS_LSCC += -DERROR=1
endif
ifdef DEBUG
  CFLAGS_LSCC += -DDEBUG=${DEBUG}
endif

CFLAGS_LSCC_SO += ${CFLAGS_LSCC}
CFLAGS_LSCC_SO += ${cflags-lscc-so}
LDFLAGS_LSCC_SO += ${LDFLAGS_LSCC}
LDFLAGS_LSCC_SO += ${ldflags-lscc-so}

CFLAGS_LSCC_A += ${CFLAGS_LSCC_SO}

ifdef DEBUG
  ifneq ($(target-lscc-y),)
    $(info CFLAGS_LSCC = ${CFLAGS_LSCC})
    $(info LDFLAGS_LSCC = ${LDFLAGS_LSCC})
  endif
endif

# LUCA support .cu and .luca suffix
# $1 - suffix of file: cu, luca
define luca_obj
$${OUTPUT}%.E.luca: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC E,$$(<),$$(@))
	$${Q}$$(LSCC) -E -o $$(@) -c $$(<) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))

$${OUTPUT}%.luca.o: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC,$$(<),$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))

$${OUTPUT}%.luca.devbin: %.${1} | $${OUTPUT}
	$(call log_obj,DEVBIN,$$(<),$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(cflags-lscc-devbin) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))

$${OUTPUT}%.luca.fatbin: %.${1} | $${OUTPUT}
	$(call log_obj,FATBIN,$$(<),$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(cflags-lscc-fatbin) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$(*))
endef
# $1 - suffix of file: cu, luca
define luca_obj_so
$${OUTPUT}%.luca.so.o: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC CC SO,$$(<),$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(CFLAGS_LSCC_SO) $$(CFLAGS_LSCC_SO_$$(*))
endef
# $1 - suffix of file: cu, luca
define luca_obj_a
$${OUTPUT}%.luca.a.o: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC CC A,$$(<),$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(CFLAGS_LSCC_A) $$(CFLAGS_LSCC_A_$$(*))
endef
$(eval $(call luca_obj,cu))
$(eval $(call luca_obj,luca))
$(eval $(call luca_obj_so,cu))
$(eval $(call luca_obj_so,luca))
$(eval $(call luca_obj_a,cu))
$(eval $(call luca_obj_a,luca))

# Example format of hc_fatbin and hcFatBinSegment, see:
# commit 798dd703bcc9 ("targets/metax.mk: add .hc_fatbin and .hcFatBinSegment targets")
# TODO: section name .hc_fatbin will be renamed.
${OUTPUT}%.luca.hc_fatbin: % | ${OUTPUT}
	$(call log_obj,HC FATBIN,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hc_fatbin $(<) $(@)

# TODO: section name .hcFatBinSegment will be renamed.
${OUTPUT}%.luca.hcFatBinSegment: % | ${OUTPUT}
	$(call log_obj,HC FATBIN SEG,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hcFatBinSegment $(<) $(@)

$(target-lscc-y): %:
	$(call log_exe,LSCC LD,$(<),$(@))
	${Q}$(LSCC) -o $(@) $(^) $(LDFLAGS_LSCC) $(LDFLAGS_LSCC_$(*))

$(target-lscc-libso-y): %:
	$(call log_exe,LSCC SO,$(<),$(@))
	${Q}$(LSCC) -o $(@) $(^) $(LDFLAGS_LSCC_SO) $(LDFLAGS_LSCC_SO_$(*))

$(target-lscc-liba-y): %:
	$(call log_exe,LSCC AR,$(<),$(@))
	${Q}ar rcs $(@) $(^)
