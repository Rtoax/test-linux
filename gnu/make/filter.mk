# SPDX-License-Identifier: GPL-3.0

OUTPUT := .output/

ifneq ($(filter %/,$(OUTPUT)),)
  $(info end with /)
endif

.PHONY: build
build:
