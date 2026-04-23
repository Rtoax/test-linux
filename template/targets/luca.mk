# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Targets list:
# - .E.luca
# - .luca.o
# - .luca.so.o
# - .luca.a.o
# - .luca.bitcode
# - .luca.devbin
# - .luca.fatbc
# - .luca.fatbin
# - .luca.lc_fatbin
# - .luca.lcFatBinSegment
# - target-lscc-y
# - target-lscc-libso-y
# - target-lscc-liba-y
#
# Input definitions:
# - LUCA_ROOT=[/opt/luca/]
# - NODEFAULTRPATH=1
# - LSCORE1000=1
# - LSCORE1002=1
#
ifndef _TARGET_LUCA_MK
_TARGET_LUCA_MK = 1

include cestc/luca.mk
include cflags.mk
include dir.mk
include string.mk

cflags-lscc-bitcode := -device-bc
cflags-lscc-devbin := -device-bin
cflags-lscc-fatbc := -fatbc
cflags-lscc-fatbin := -fatbin
cflags-lscc-so := -Xcompiler -fPIC
ldflags-lscc-so := -shared -Xcompiler -fPIC

CFLAGS_LSCC += -I${TOPDIR}/libs/
CFLAGS_LSCC += -I${TOPDIR}/hpc/nvidia/cuda/
CFLAGS_LSCC += -I${TOPDIR}/hpc/nvidia/cuda/adapter/include/
CFLAGS_LSCC += -DHAVE_LUCA=1
CFLAGS_LSCC += -D__USE_LUCA__=1

ifneq ($(wildcard ${LUCA_CU_BRIDGE}),)
  CFLAGS_LSCC += -I${LUCA_CU_BRIDGE} -DLUCA_CU_BRIDGE=1
endif
ifdef HAVE_LCDNN
  CFLAGS_LSCC += -DHAVE_LCDNN=1
endif
ifdef HAVE_LCFILE
  CFLAGS_LSCC += -DHAVE_LCFILE=1
endif
ifdef HAVE_LCPTI
  CFLAGS_LSCC += -DHAVE_LCPTI=1
endif
ifdef HAVE_LSVPU
  CFLAGS_LSCC += -DHAVE_LSVPU=1
endif

ifneq ($(LUCA_VERSION_MAJOR}),)
  CFLAGS_LSCC += -DLUCA_VERSION_MAJOR=${LUCA_VERSION_MAJOR}
  CFLAGS_LSCC += -DLUCA_VERSION_MINOR=${LUCA_VERSION_MINOR}
  CFLAGS_LSCC += -DLUCA_VERSION_PATCH=${LUCA_VERSION_PATCH}
endif

# FIXME: In file included from sparse.luca:6:
# In file included from /opt/luca/include/lcsparse/lcsparse.h:9:
# /opt/luca/include/lcsparse/interface/lcsp_conversion.h:8:10: fatal error: 'common/lcsp_types.h' file not found
# #include "common/lcsp_types.h"
#          ^~~~~~~~~~~~~~~~~~~~~
CFLAGS_LSCC += -I${LUCA_ROOT}/include/lcsparse/
CFLAGS_LSCC += -I${LUCA_ROOT}/include/lcblas/

LDFLAGS_LSCC += -llccl
LDFLAGS_LSCC += -llcblas -llcblasLt
LDFLAGS_LSCC += -llcfft
LDFLAGS_LSCC += -llcrand
LDFLAGS_LSCC += -llcsparse
LDFLAGS_LSCC += -llcsolver
ifdef HAVE_LCFILE
  LDFLAGS_LSCC += -llcfile
endif
ifdef HAVE_LCPTI
  LDFLAGS_LSCC += -llcpti
endif
ifdef HAVE_LSVPU
  LDFLAGS_LSCC += -llsvpu
endif

ifdef NODEFAULTRPATH
  # Remove default so search directory, see ldflags: -Wl,-rpath,/path/to/so/
  LDFLAGS_LSCC += -nodefaultrpath
endif
ifdef LSCORE1000
  CFLAGS_LSCC += --offload-arch lscore1000
else ifdef LSCORE1002
  CFLAGS_LSCC += --offload-arch lscore1002
endif

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
	$(call log_obj,LSCC E,$$(@))
	$${Q}$$(LSCC) -E -o $$(@) -c $$(<) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))

$${OUTPUT}%.luca.o: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC,$$(@))
	$${Q}$$(LSCC) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))

$${OUTPUT}%.luca.bitcode: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC BC,$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(cflags-lscc-bitcode) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))

$${OUTPUT}%.luca.devbin: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC DEVBIN,$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(cflags-lscc-devbin) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))

$${OUTPUT}%.luca.fatbin: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC FATBIN,$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(cflags-lscc-fatbin) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))

$${OUTPUT}%.luca.fatbc: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC FATBC,$$(@))
	$${Q}$$(LSCC) -o $$(@) -c $$(<) $$(cflags-lscc-fatbc) $$(CFLAGS_LSCC) $$(CFLAGS_LSCC_$$(*))
endef
# $1 - suffix of file: cu, luca
define luca_obj_so
$${OUTPUT}%.luca.so.o: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC CC SO,$$(@))
	$${Q}$$(LSCC) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CFLAGS_LSCC_SO) $$(CFLAGS_LSCC_SO_$$(*))
endef
# $1 - suffix of file: cu, luca
define luca_obj_a
$${OUTPUT}%.luca.a.o: %.${1} | $${OUTPUT}
	$(call log_obj,LSCC CC A,$$(@))
	$${Q}$$(LSCC) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CFLAGS_LSCC_A) $$(CFLAGS_LSCC_A_$$(*))
endef
$(eval $(call luca_obj,cu))
$(eval $(call luca_obj,luca))
$(eval $(call luca_obj_so,cu))
$(eval $(call luca_obj_so,luca))
$(eval $(call luca_obj_a,cu))
$(eval $(call luca_obj_a,luca))

# Example format of lc_fatbin and lcFatBinSegment, see:
# commit 798dd703bcc9 ("targets/hpcc.mk: add .lc_fatbin and .lcFatBinSegment targets")
# TODO: section name .lc_fatbin will be renamed.
${OUTPUT}%.luca.lc_fatbin: % | ${OUTPUT}
	$(call log_obj,HC FATBIN,$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.lc_fatbin $(<) $(@)

# TODO: section name .lcFatBinSegment will be renamed.
${OUTPUT}%.luca.lcFatBinSegment: % | ${OUTPUT}
	$(call log_obj,HC FATBIN SEG,$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.lcFatBinSegment $(<) $(@)

$(target-lscc-y): %:
	$(call log_tgt,LSCC LD,$(@))
	${Q}$(LSCC) -o $(@) $(^) $(LDFLAGS_LSCC) $(LDFLAGS_LSCC_$(*))

$(target-lscc-libso-y): %:
	$(call log_tgt,LSCC SO,$(@))
	${Q}$(LSCC) -o $(@) $(^) $(LDFLAGS_LSCC_SO) $(LDFLAGS_LSCC_SO_$(*))

$(target-lscc-liba-y): %:
	$(call log_tgt,LSCC AR,$(@))
	${Q}ar rcs $(@) $(^)

# append ${OUTPUT} for each object
$(foreach lib, ${target-lscc-libso-y} ${target-lscc-liba-y}, \
  $(eval ${lib}-objs := $(call append_output_prefix,${${lib}-objs})) \
  $(if ${DEBUG},$(info ${lib}-objs = ${${lib}-objs})) \
)

$(foreach lib, ${target-lscc-libso-y}, $(eval ${lib}: $${${lib}-objs}))
$(foreach lib, ${target-lscc-liba-y}, $(eval ${lib}: $${${lib}-objs}))

# Depends, like:
# hello: hello.luca.o
# hello-luca: hello.luca.o
$(foreach t, ${target-lscc-y}, \
  $(if $(shell test -f ${t}.cu && echo yes), \
    $(if ${DEBUG}, $(info Dep ${t}: ${OUTPUT}${t}.luca.o $${${t}-objs} ${LUCA_HELPERS})) \
    $(eval ${t}: ${OUTPUT}${t}.luca.o $${${t}-objs} ${LUCA_HELPERS}), \
    $(eval tname := $(call strip_tail,${t},-luca)) \
    $(if $(shell test -f ${tname}.cu && echo yes), \
      $(if ${DEBUG}, $(info Dep ${t}: ${OUTPUT}${tname}.luca.o $${${t}-objs} ${LUCA_HELPERS})) \
      $(eval ${t}: ${OUTPUT}${tname}.luca.o $${${t}-objs} ${LUCA_HELPERS}), \
      $(if ${DEBUG}, $(info Dep(${tname}) ${t}: $${${t}-objs} ${LUCA_HELPERS})) \
      $(eval ${t}: $${${t}-objs} ${LUCA_HELPERS}) \
    ) \
  ) \
)

$(foreach t, ${target-lscc-y}, \
  $(if $(shell test -f ${OUTPUT}${t}.luca.o.d && echo yes), \
    $(if ${DEBUG}, $(info Include ${OUTPUT}${t}.luca.o.d)) \
    $(eval include ${OUTPUT}${t}.luca.o.d), \
    $(eval depname := ${OUTPUT}$(call strip_tail,${t},-luca).luca.o.d) \
    $(if $(shell test -f ${depname} && echo yes), \
      $(if ${DEBUG}, $(info Include ${depname})) \
      $(eval include ${depname}), \
      $(if ${DEBUG}, $(info Not found ${depname})) \
    ) \
  ) \
)

$(foreach so, ${target-lscc-libso-y} ${target-lscc-liba-y}, \
  $(foreach obj, ${${so}-objs}, \
    $(if $(shell test -f ${obj}.d && echo yes), \
      $(if ${DEBUG}, $(info Include ${obj}.d)) \
      $(eval include ${obj}.d), \
      $(if ${DEBUG}, $(info Not found ${obj}.d)) \
    ) \
  ) \
)

endif
