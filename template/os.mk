# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Output definitions:
# - OS_ID=
# - OS_VERSION_ID=
#
_OS = 1

OS_ID := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | tr -d '"')
OS_VERSION_ID := $(shell grep ^VERSION_ID= /etc/os-release | sed 's/VERSION_ID=//g' | tr -d '"')

ifdef DEBUG
  $(info OS_ID = ${OS_ID})
  $(info OS_VERSION_ID = ${OS_VERSION_ID})
endif

ifeq ($(OS_VERSION_ID),)
  $(error Not found VERSION_ID in /etc/os-release)
endif

export OS_ID OS_VERSION_ID
