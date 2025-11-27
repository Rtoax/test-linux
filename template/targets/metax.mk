# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
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
# - target-htcc-liba-y

_TARGET_METAX = 1

include hpcc.mk

cflags-htcc-devbin := -device-bin
cflags-htcc-fatbin := -fatbin
cflags-htcc-so := -Xcompiler -fPIC
ldflags-htcc-so := -shared -Xcompiler -fPIC


CFLAGS_HTCC += -DHAVE_HPCC=1
CFLAGS_HTCC += -D__USE_HPCC__=1

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

# FIXME: warning: 'visibility' attribute ignored
CFLAGS_HTCC += -Wno-ignored-attributes

LDFLAGS_HTCC += -lhccl
LDFLAGS_HTCC += -lhcblas -lhcblasLt
LDFLAGS_HTCC += -lhcfft
LDFLAGS_HTCC += -lhcrand
LDFLAGS_HTCC += -lhcsparse

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
	$(call log_obj,HTCC E,$$(<),$$(@))
	$${Q}$$(HTCC) -E -o $$(@) -c $$(<) $$(CFLAGS_HTCC) $$(CFLAGS_HTCC_$$(*))

$${OUTPUT}%.hpcc.o: %.${1} | $${OUTPUT}
	$(call log_obj,HTCC,$$(<),$$(@))
	$${Q}$$(HTCC) -o $$(@) -c $$(<) $$(CFLAGS_HTCC) $$(CFLAGS_HTCC_$$(*))

$${OUTPUT}%.hpcc.devbin: %.${1} | $${OUTPUT}
	$(call log_obj,DEVBIN,$$(<),$$(@))
	$${Q}$$(HTCC) -o $$(@) -c $$(<) $$(cflags-htcc-devbin) $$(CFLAGS_HTCC) $$(CFLAGS_HTCC_$$(*))

$${OUTPUT}%.hpcc.fatbin: %.${1} | $${OUTPUT}
	$(call log_obj,FATBIN,$$(<),$$(@))
	$${Q}$$(HTCC) -o $$(@) -c $$(<) $$(cflags-htcc-fatbin) $$(CFLAGS_HTCC) $$(CFLAGS_HTCC_$$(*))
endef
# $1 - suffix of file: hpcc, cu
define hpcc_obj_so
$${OUTPUT}%.hpcc.so.o: %.${1} | $${OUTPUT}
	$(call log_obj,HTCC CC SO,$$(<),$$(@))
	$${Q}$$(HTCC) -o $$(@) -c $$(<) $$(CFLAGS_HTCC_SO) $$(CFLAGS_HTCC_SO_$$(*))
endef
# $1 - suffix of file: hpcc, cu
define hpcc_obj_a
$${OUTPUT}%.hpcc.a.o: %.${1} | $${OUTPUT}
	$(call log_obj,HTCC CC A,$$(<),$$(@))
	$${Q}$$(HTCC) -o $$(@) -c $$(<) $$(CFLAGS_HTCC_A) $$(CFLAGS_HTCC_A_$$(*))
endef
$(eval $(call hpcc_obj,cu))
$(eval $(call hpcc_obj,hpcc))
$(eval $(call hpcc_obj_so,cu))
$(eval $(call hpcc_obj_so,hpcc))
$(eval $(call hpcc_obj_a,cu))
$(eval $(call hpcc_obj_a,hpcc))

# Example format of hc_fatbin and hcFatBinSegment, see:
# commit 798dd703bcc9 ("targets/metax.mk: add .hc_fatbin and .hcFatBinSegment targets")
${OUTPUT}%.hpcc.hc_fatbin: % | ${OUTPUT}
	$(call log_obj,HC FATBIN,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hc_fatbin $(<) $(@)

${OUTPUT}%.hpcc.hcFatBinSegment: % | ${OUTPUT}
	$(call log_obj,HC FATBIN SEG,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.hcFatBinSegment $(<) $(@)

$(target-htcc-y): %:
	$(call log_exe,HTCC LD,$(<),$(@))
	${Q}$(HTCC) -o $(@) $(^) $(LDFLAGS_HTCC) $(LDFLAGS_HTCC_$(*))

$(target-htcc-libso-y): %:
	$(call log_exe,HTCC SO,$(<),$(@))
	${Q}$(HTCC) -o $(@) $(^) $(LDFLAGS_HTCC_SO) $(LDFLAGS_HTCC_SO$(*))

$(target-htcc-liba-y): %:
	$(call log_exe,HTCC AR,$(<),$(@))
	${Q}ar rcs $(@) $(^)
