# SPDX-License-Identifier: GPL-3.0

KVERSION_RAW := $(shell uname -r | grep -o '^[0-9]\.[0-9]*\.[0-9]*')
KVERSION := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$1}')
KPATCHLEVEL := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$2}')
KSUBLEVEL := $(shell echo ${KVERSION_RAW} | awk -F '.' '{print $$3}')
KVERSION_CODE := $(shell echo "$$(( (${KVERSION}<<16) + (${KPATCHLEVEL}<<8) + (${KSUBLEVEL}>255?255:${KSUBLEVEL}) ))" )

KFLAGS :=
KFLAGS += -DKVERSION=$(KVERSION)
KFLAGS += -DKPATCHLEVEL=$(KPATCHLEVEL)
KFLAGS += -DKSUBLEVEL=$(KSUBLEVEL)

# See linux/version.h
define kernel_version
$(shell echo "$$(( (${1}<<16) + (${2}<<8) + (${3}>255?255:${3}) ))")
endef

ifneq (${KVERSION_CODE},$(call kernel_version,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  $(error "Bad KVERSION_CODE ${KVERSION_CODE}")
endif

ifdef DEBUG
  $(info KVERSION = ${KVERSION}.${KPATCHLEVEL}.${KSUBLEVEL}, CODE ${KVERSION_CODE})
  $(info kernel_version(${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}) = \
	  $(call kernel_version,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
endif
