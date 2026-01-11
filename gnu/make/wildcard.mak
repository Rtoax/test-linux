# SPDX-License-Identifier: GPL-3.0
FILE := /etc/os-release

ifeq ($(wildcard ${FILE}),)
  $(error ERROR: ${FILE} is not exist)
else
  $(info INFO: Found ${FILE})
endif

.PHONY: build
build:
