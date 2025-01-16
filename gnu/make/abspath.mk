# SPDX-License-Identifier: GPL-3.0

$(info abspath = $(abspath /a/b/c))
$(info abspath MAKEFILE_LIST = $(abspath ${MAKEFILE_LIST}))

.PHONY: build
build:
