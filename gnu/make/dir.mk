# SPDX-License-Identifier: GPL-3.0
path := /a/b/c

$(info path = ${path})
$(info dir = $(dir ${path}))
$(info notdir = $(notdir ${path}))
$(info basename = $(basename ${path}))

.PHONY: build
build:
