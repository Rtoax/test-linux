# SPDX-License-Identifier: GPL-3.0

OS_RELEASE := /etc/os-release
CUDA := /usr/local/cuda

$(info OS_RELEASE $(shell realpath ${OS_RELEASE}))
ifneq ($(wildcard ${CUDA}),)
  $(info CUDA $(shell realpath ${CUDA}))
endif

.PHONY: build
build:
