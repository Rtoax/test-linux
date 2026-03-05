# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - OS_ID=[fedora|ubuntu]
#
# - OS_VERSION_ID=[43|24.04]
#
# - OS_CFLAGS+=-DOS_ID=[fedora|ubuntu]
#   OS_CFLAGS+=-DOS_FEDORA=1
#   OS_CFLAGS+=-DOS_UBUNTU=1
#   OS_CFLAGS+=-DOS_VERSION_ID=[43|24.03]
#   OS_CFLAGS+=-DOS_VERSION_ID_MAJOR=[43|24]
#   OS_CFLAGS+=-DOS_VERSION_ID_MINOR=[|04]
#      C source code should use OS_ID like:
#      #if OS_ID == fedora
#      #pragma message fedora
#      #endif
#
ifndef _OS_MK
_OS_MK = 1

OS_CFLAGS :=

get_distr_info = $(patsubst "%",%,$(shell grep $(1) /etc/os-release 2>/dev/null | \
					awk -F'=' '{print $$2}'))

OS_ID := $(call get_distr_info, '^ID=')
OS_VERSION_ID := $(call get_distr_info, '^VERSION_ID=')
OS_VERSION_ID_MAJOR := $(shell echo ${OS_VERSION_ID} | awk -F '.' '{print $$1}')
OS_VERSION_ID_MINOR := $(shell echo ${OS_VERSION_ID} | awk -F '.' '{print $$2}')

ifeq ($(OS_VERSION_ID),)
  $(error Not found VERSION_ID in /etc/os-release)
endif

OS_CFLAGS += -DOS_ID=${OS_ID}
ifeq (${OS_ID},fedora)
  OS_CFLAGS := -DOS_FEDORA=1
else ifeq (${OS_ID},ubuntu)
  OS_CFLAGS := -DOS_UBUNTU=1
else
  $(error "Not support ${OS_ID}, please add it to template/os.mk")
endif

OS_CFLAGS += -DOS_VERSION_ID=${OS_VERSION_ID}
OS_CFLAGS += -DOS_VERSION_ID_MAJOR=${OS_VERSION_ID_MAJOR}
ifneq (${OS_VERSION_ID_MINOR},)
  OS_CFLAGS += -DOS_VERSION_ID_MINOR=${OS_VERSION_ID_MINOR}
endif

ifdef DEBUG
  $(info OS_ID = ${OS_ID})
  $(info OS_VERSION_ID = ${OS_VERSION_ID})
  $(info OS_VERSION_ID_MAJOR = ${OS_VERSION_ID_MAJOR})
  $(info OS_VERSION_ID_MINOR = ${OS_VERSION_ID_MINOR})
  $(info OS_CFLAGS = ${OS_CFLAGS})
endif

export OS_ID
export OS_VERSION_ID
export OS_VERSION_ID_MAJOR
export OS_VERSION_ID_MINOR
export OS_CFLAGS

endif
