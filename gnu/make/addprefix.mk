# SPDX-License-Identifier: GPL-3.0

FILES := a b c
PREFIX := $(shell pwd)/

$(info FILES: ${FILES})

FILES := $(addprefix ${PREFIX},${FILES})

$(info FILES: ${FILES})

.PHONY: build
build:
