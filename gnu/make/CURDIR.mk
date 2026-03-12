# SPDX-License-Identifier: GPL-3.0

$(info CURDIR = $(CURDIR))

ifeq (${CURDIR},)
  $(error not found CURDIR)
endif

.PHONY: build
build:
