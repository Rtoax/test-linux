# SPDX-License-Identifier: GPL-3.0
# WARNING: If you are inside a container, the kernel version queried by uame -r
# may not match the environment inside the container, so it is normal if
# compilation errors occur.

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

# argument: [-gt|-eq|-lt],x,y,z
define kernel_compare
$(shell if [[ ${KVERSION_CODE} ${1} $(call kernel_version,${2},${3},${4}) ]]; then \
		echo y; \
	else echo n; \
	fi)
endef

define kernel_newer_than
$(call kernel_compare,-gt,${1},${2},${3})
endef
define kernel_equal_to
$(call kernel_compare,-eq,${1},${2},${3})
endef
define kernel_lower_than
$(call kernel_compare,-lt,${1},${2},${3})
endef

ifneq (${KVERSION_CODE},$(call kernel_version,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  $(error "Bad KVERSION_CODE ${KVERSION_CODE}")
endif
ifneq ($(call kernel_equal_to,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}),y)
  $(error "call kernel_equal_to failed")
endif

ifdef DEBUG
  $(info KVERSION = ${KVERSION}.${KPATCHLEVEL}.${KSUBLEVEL}, CODE ${KVERSION_CODE})
  $(info kernel_version(${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}) = \
	  $(call kernel_version,${KVERSION},${KPATCHLEVEL},${KSUBLEVEL}))
  # we'll not running kernel v1.1.1 anywhere
  $(info kernel_newer_than(1,1,1) = $(call kernel_newer_than,1,1,1))
  # newest kernel is v6.14
  $(info kernel_newer_than(7,0,0) = $(call kernel_newer_than,7,0,0))
endif
