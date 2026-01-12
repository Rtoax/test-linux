# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - OS_ID=[fedora]
# - OS_VERSION_ID=[43]
#
_OS_MK = 1

OS_ID := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | tr -d '"')
OS_VERSION_ID := $(shell grep ^VERSION_ID= /etc/os-release | sed 's/VERSION_ID=//g' | tr -d '"')

ifeq ($(OS_VERSION_ID),)
  $(error Not found VERSION_ID in /etc/os-release)
endif

ifdef DEBUG
  $(info OS_ID = ${OS_ID})
  $(info OS_VERSION_ID = ${OS_VERSION_ID})
endif

export OS_ID OS_VERSION_ID
