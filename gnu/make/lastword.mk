# SPDX-License-Identifier: GPL-3.0

$(info lastword = $(lastword /a/b/c))
$(info lastword MAKEFILE_LIST = $(lastword ${MAKEFILE_LIST}))

.PHONY: build
build:
