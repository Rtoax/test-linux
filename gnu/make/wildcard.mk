# SPDX-License-Identifier: GPL-3.0
SHELL = bash

ifeq ($(wildcard /etc/os-release),)
  $(error ERROR: /etc/os-release is not exist)
else
  $(info INFO: Found /etc/os-release)
endif

.PHONY: build
build:
