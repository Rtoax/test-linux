# SPDX-License-Identifier: GPL-3.0
SHELL := bash

GO := $(shell which go 2>/dev/null)

ifeq ($(wildcard $(GO)),)
  $(error Please install golang)
endif

