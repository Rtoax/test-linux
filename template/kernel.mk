# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Exports:
# - KVERSION
# - KPATCHLEVEL
# - KSUBLEVEL
# - KVERSION_CODE
# - KUAPIVERSION
# - KUAPIPATCHLEVEL
# - KUAPISUBLEVEL
# - KUAPIVERSION_CODE
#
# Functions:
# - kver_gt
# - kver_eq
# - kver_lt
# - kver_uapi_gt
# - kver_uapi_eq
# - kver_uapi_lt
#
# WARNING: If you are inside a container, the kernel version queried by uame -r
# may not match the environment inside the container, so it is normal if
# compilation errors occur.
_KERNEL = 1

SHELL := /bin/bash

KVER_GREP_CMD := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'

KVERSION_RAW := $(shell uname -r | ${KVER_GREP_CMD} | head -1)
KVERSION := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$1}')
KPATCHLEVEL := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$2}')
KSUBLEVEL := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$3}')
KVERSION_CODE := $(shell echo "$$(( (${KVERSION}<<16) + (${KPATCHLEVEL}<<8) + (${KSUBLEVEL}>255?255:${KSUBLEVEL}) ))" )

KUAPI_VERSION_H := /usr/include/linux/version.h
KUAPI_VERSION_RAW := $(shell rpm -q --queryformat='%{VERSION}' kernel-headers 2>/dev/null \
				| ${KVER_GREP_CMD} || \
			dpkg-query -W -f='$${Version}' linux-libc-dev 2>/dev/null \
				| ${KVER_GREP_CMD})
ifeq ($(KUAPI_VERSION_RAW),)
  $(error Not found kernel-headers or linux-libc-dev on your system)
endif
KUAPIVERSION := $(shell echo ${KUAPI_VERSION_RAW} | awk -F '.' '{print $$1}')
KUAPIPATCHLEVEL := $(shell echo ${KUAPI_VERSION_RAW} | awk -F '.' '{print $$2}')
KUAPISUBLEVEL := $(shell echo ${KUAPI_VERSION_RAW} | awk -F '.' '{print $$3}')
KUAPIVERSION_CODE := $(shell echo "$$(( (${KUAPIVERSION}<<16) + (${KUAPIPATCHLEVEL}<<8) + (${KUAPISUBLEVEL}>255?255:${KUAPISUBLEVEL}) ))" )

KFLAGS :=
KFLAGS += -DKVERSION=$(KVERSION)
KFLAGS += -DKPATCHLEVEL=$(KPATCHLEVEL)
KFLAGS += -DKSUBLEVEL=$(KSUBLEVEL)

# See linux/version.h
define kernel_version
$(shell echo "$$(( (${1}<<16) + (${2}<<8) + (${3}>255?255:${3}) ))")
endef

# argument: kcode,[-gt|-eq|-lt],x,y,z
define kernel_compare
$(shell if [[ ${1} ${2} $(call kernel_version,${3},${4},${5}) ]]; then \
		echo y; \
	else echo n; \
	fi)
endef

define kver_gt
$(call kernel_compare,${KVERSION_CODE},-gt,${1},${2},${3})
endef
define kver_eq
$(call kernel_compare,${KVERSION_CODE},-eq,${1},${2},${3})
endef
define kver_lt
$(call kernel_compare,${KVERSION_CODE},-lt,${1},${2},${3})
endef
define kver_uapi_gt
$(call kernel_compare,${KUAPIVERSION_CODE},-gt,${1},${2},${3})
endef
define kver_uapi_eq
$(call kernel_compare,${KUAPIVERSION_CODE},-eq,${1},${2},${3})
endef
define kver_uapi_lt
$(call kernel_compare,${KUAPIVERSION_CODE},-lt,${1},${2},${3})
endef

ifneq (${KVERSION_CODE},$(call kernel_version,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  $(error "Bad KVERSION_CODE ${KVERSION_CODE}")
endif
ifneq (${KUAPIVERSION_CODE},$(call kernel_version,${KUAPIVERSION},${KUAPIPATCHLEVEL},${KUAPISUBLEVEL}))
  $(error "Bad KUAPIVERSION_CODE ${KUAPIVERSION_CODE}")
endif
# no body use linux-1.1.1 i think
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
# newest kernel is v6.14 right now
ifneq ($(call kver_lt,7,0,0),y)
  $(error "call kver_lt failed")
endif
ifneq ($(call kver_uapi_lt,7,0,0),y)
  $(error "call kver_uapi_lt failed")
endif

export KVERSION KPATCHLEVEL KSUBLEVEL KVERSION_CODE
export KUAPIVERSION KUAPIPATCHLEVEL KUAPISUBLEVEL KUAPIVERSION_CODE

ifdef DEBUG
  $(info KVERSION = ${KVERSION}.${KPATCHLEVEL}.${KSUBLEVEL}, CODE ${KVERSION_CODE})
  $(info KUAPIVERSION = ${KUAPIVERSION}.${KUAPIPATCHLEVEL}.${KUAPISUBLEVEL}, CODE ${KUAPIVERSION_CODE})
  $(info kernel_version(${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}) = \
	  $(call kernel_version,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  $(info kver_gt(1,1,1) = $(call kver_gt,1,1,1))
  $(info kver_eq(${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}) = \
	  $(call kver_eq,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  $(info kver_lt(7,0,0) = $(call kver_lt,7,0,0))
endif
