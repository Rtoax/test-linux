# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - OS_ID=[fedora]
# - OS_VERSION_ID=[43]
#
ifndef _OS_MK
_OS_MK = 1

get_distr_info = $(patsubst "%",%,$(shell grep $(1) /etc/os-release 2>/dev/null | \
					awk -F'=' '{print $$2}'))

OS_ID := $(call get_distr_info, '^ID=')
OS_VERSION_ID := $(call get_distr_info, '^VERSION_ID=')

ifeq ($(OS_VERSION_ID),)
  $(error Not found VERSION_ID in /etc/os-release)
endif

ifdef DEBUG
  $(info OS_ID = ${OS_ID})
  $(info OS_VERSION_ID = ${OS_VERSION_ID})
endif

export OS_ID OS_VERSION_ID

endif
