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
# - kver_{gt,ge,eq,lt,le}()=[y|n]
# - kver_uapi_{gt,ge,eq,lt,le}()=[y|n]
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

$(eval $(call define_version,kver,version3_code1688,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
$(eval $(call define_version,kver_uapi,version3_code1688,${KUAPIVERSION},${KUAPIPATCHLEVEL},${KUAPISUBLEVEL}))

export KVERSION KPATCHLEVEL KSUBLEVEL KVERSION_CODE
export KUAPIVERSION KUAPIPATCHLEVEL KUAPISUBLEVEL KUAPIVERSION_CODE
export KFLAGS

ifdef DEBUG
  $(info KVERSION = ${KVERSION}.${KPATCHLEVEL}.${KSUBLEVEL}, CODE ${KVERSION_CODE})
  $(info KUAPIVERSION = ${KUAPIVERSION}.${KUAPIPATCHLEVEL}.${KUAPISUBLEVEL}, CODE ${KUAPIVERSION_CODE})
  $(info KFLAGS = ${KFLAGS})
endif

# no body use linux v1.1.1 i think
ifneq ($(call kver_gt,1,1,1),y)
  $(error "call kver_gt failed")
endif
ifneq ($(call kver_uapi_gt,1,1,1),y)
  $(error "call kver_uapi_gt failed")
endif
# Newest kernel is v7.1
# see https://github.com/torvalds/linux
ifneq ($(call kver_lt,7,3,0),y)
  $(error "call kver_lt failed, kver >= 7.3.0")
endif
ifneq ($(call kver_uapi_lt,7,2,0),y)
  $(error "call kver_uapi_lt failed, kuapi version >= 7.2.0")
endif
ifneq (${KVERSION_CODE},${kver_VERSION_CODE})
  $(error define_version failed for kver)
endif
ifneq (${KUAPIVERSION_CODE},${kver_uapi_VERSION_CODE})
  $(error define_version failed for kver_uapi)
endif

endif
