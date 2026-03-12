# SPDX-License-Identifier: GPL-3.0

include dir.mk
include shell.mk

$(info lastword = $(lastword /a/b/c))
$(info lastword MAKEFILE_LIST = $(lastword ${MAKEFILE_LIST}))
$(info firstword MAKECMDGOALS = $(firstword $(MAKECMDGOALS)))
$(info firstword MAKEFILE_LIST = $(firstword $(MAKEFILE_LIST)))
$(info abspath lastword MAKEFILE_LIST = $(abspath $(lastword ${MAKEFILE_LIST})))

.PHONY: build
build:
