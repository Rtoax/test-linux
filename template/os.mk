# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
_OS = 1

OS := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | tr -d '"')

ifdef DEBUG
  $(info OS = ${OS})
endif
