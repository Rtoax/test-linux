# SPDX-License-Identifier: GPL-3.0

include template/ansi.mk
include template/emoji.mk

$(info MOONLIGHT = ${MOONLIGHT})
$(info MAKEFILE_LIST = ${MAKEFILE_LIST})
$(info MAKEFLAGS = ${MAKEFLAGS})

.PHONY: build
build:
