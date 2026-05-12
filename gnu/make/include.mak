# SPDX-License-Identifier: GPL-3.0
#
include included.mak

$(info MAKEFILE_LIST = ${MAKEFILE_LIST})

$(info current_makefile = $(call current_makefile))

.PHONY: build
build:
