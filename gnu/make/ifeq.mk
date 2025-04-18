# SPDX-License-Identifier: GPL-3.0

ifeq ($(shell uname -m),x86_64)
  $(info x86_64)
else ifeq ($(shell uname -m),aarch64)
  $(info aarch64)
endif

.PHONY: build
build:

