# SPDX-License-Identifier: GPL-3.0

include template/ansi.mk
include template/emoji.mk

$(info EMOJI_MOONS = ${EMOJI_MOONS})
$(info MAKEFILE_LIST = ${MAKEFILE_LIST})
$(info MAKEFLAGS = ${MAKEFLAGS})

.PHONY: build
build:
