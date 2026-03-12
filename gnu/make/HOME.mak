# SPDX-License-Identifier: GPL-3.0

$(info HOME = $(HOME))

ifeq (${HOME},)
  $(error not found HOME)
endif

.PHONY: build
build:
