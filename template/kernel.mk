# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# WARNING: If you are inside a container, the kernel version queried by uame -r
# may not match the environment inside the container, so it is normal if
# compilation errors occur.
#
# Exports:
# - KVERSION=
# - KPATCHLEVEL=
# - KSUBLEVEL=
# - KVERSION_CODE=
# - KUAPIVERSION=
# - KUAPIPATCHLEVEL=
# - KUAPISUBLEVEL=
# - KUAPIVERSION_CODE=
# - KFLAGS=
#
# Functions:
# - kver_gt()=[y|n]
# - kver_ge()=[y|n]
# - kver_eq()=[y|n]
# - kver_lt()=[y|n]
# - kver_le()=[y|n]
# - kver_uapi_gt()=[y|n]
# - kver_uapi_eq()=[y|n]
# - kver_uapi_lt()=[y|n]
#
ifndef _KERNEL_MK
_KERNEL_MK = 1

include dir.mk
include shell.mk
include version.mk

kversh = ${TOPDIR}/scripts/version/linux.sh

KVERSION := $(shell ${kversh} --major)
KPATCHLEVEL := $(shell ${kversh} --patchlevel)
KSUBLEVEL := $(shell ${kversh} --sublevel)
KVERSION_CODE := $(shell ${kversh} --code)

KUAPIVERSION := $(shell ${kversh} --uapimajor)
KUAPIPATCHLEVEL := $(shell ${kversh} --uapipatchlevel)
KUAPISUBLEVEL := $(shell ${kversh} --uapisublevel)
KUAPIVERSION_CODE := $(shell ${kversh} --uapicode)

KFLAGS :=
KFLAGS += -DKVERSION=$(KVERSION)
KFLAGS += -DKPATCHLEVEL=$(KPATCHLEVEL)
KFLAGS += -DKSUBLEVEL=$(KSUBLEVEL)

define kver_gt
$(call version3_code1688_cmp,${KVERSION_CODE},-gt,${1},${2},${3})
endef
define kver_ge
$(call version3_code1688_cmp,${KVERSION_CODE},-ge,${1},${2},${3})
endef
define kver_eq
$(call version3_code1688_cmp,${KVERSION_CODE},-eq,${1},${2},${3})
endef
define kver_lt
$(call version3_code1688_cmp,${KVERSION_CODE},-lt,${1},${2},${3})
endef
define kver_le
$(call version3_code1688_cmp,${KVERSION_CODE},-le,${1},${2},${3})
endef
define kver_uapi_gt
$(call version3_code1688_cmp,${KUAPIVERSION_CODE},-gt,${1},${2},${3})
endef
define kver_uapi_eq
$(call version3_code1688_cmp,${KUAPIVERSION_CODE},-eq,${1},${2},${3})
endef
define kver_uapi_lt
$(call version3_code1688_cmp,${KUAPIVERSION_CODE},-lt,${1},${2},${3})
endef

export KVERSION KPATCHLEVEL KSUBLEVEL KVERSION_CODE
export KUAPIVERSION KUAPIPATCHLEVEL KUAPISUBLEVEL KUAPIVERSION_CODE
export KFLAGS

ifdef DEBUG
  $(info KVERSION = ${KVERSION}.${KPATCHLEVEL}.${KSUBLEVEL}, CODE ${KVERSION_CODE})
  $(info KUAPIVERSION = ${KUAPIVERSION}.${KUAPIPATCHLEVEL}.${KUAPISUBLEVEL}, CODE ${KUAPIVERSION_CODE})
  $(info KFLAGS = ${KFLAGS})
  $(info version3_code1688(${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}) = \
         $(call version3_code1688,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  $(info kver_gt(1,1,1) = $(call kver_gt,1,1,1))
  $(info kver_eq(${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}) = \
         $(call kver_eq,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  $(info kver_lt(7,0,0) = $(call kver_lt,7,0,0))
endif

ifneq (${KVERSION_CODE},$(call version3_code1688,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  $(error "Bad KVERSION_CODE ${KVERSION_CODE}")
endif
ifneq (${KUAPIVERSION_CODE},$(call version3_code1688,${KUAPIVERSION},${KUAPIPATCHLEVEL},${KUAPISUBLEVEL}))
  $(error "Bad KUAPIVERSION_CODE ${KUAPIVERSION_CODE}")
endif
# no body use linux v1.1.1 i think
ifneq ($(call kver_gt,1,1,1),y)
  $(error "call kver_gt failed")
endif
ifneq ($(call kver_uapi_gt,1,1,1),y)
  $(error "call kver_uapi_gt failed")
endif
ifneq ($(call kver_eq,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}),y)
  $(error "call kver_eq failed")
endif
ifneq ($(call kver_uapi_eq,${KUAPIVERSION},${KUAPIPATCHLEVEL},${KUAPISUBLEVEL}),y)
  $(error "call kver_uapi_eq failed")
endif
# newest kernel is v7.0 right now
ifneq ($(call kver_lt,7,1,0),y)
  $(error "call kver_lt failed")
endif
ifneq ($(call kver_uapi_lt,7,0,0),y)
  $(error "call kver_uapi_lt failed")
endif

endif
