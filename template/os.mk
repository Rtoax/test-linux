# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - OS_ID=[fedora]
# - OS_VERSION_ID=[43]
# - OS_CFLAGS=-DOS_ID=[fedora] -DOS_VERSION_ID=[43]
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

ifeq ($(OS_VERSION_ID),)
  $(error Not found VERSION_ID in /etc/os-release)
endif

OS_CFLAGS += -DOS_ID=${OS_ID}
OS_CFLAGS += -DOS_VERSION_ID=${OS_VERSION_ID}

ifdef DEBUG
  $(info OS_ID = ${OS_ID})
  $(info OS_VERSION_ID = ${OS_VERSION_ID})
  $(info OS_CFLAGS = ${OS_CFLAGS})
endif

export OS_ID OS_VERSION_ID

endif
