# SPDX-License-Identifier: GPL-3.0
path := /a/b/c-d.c
path += /c/d/e.c

$(info path = ${path})
$(info path obj = ${path:.c=.o})
$(info path obj c name = $(subst -,_,${path:.c=.o}))
$(info dir = $(dir ${path}))
$(info notdir = $(notdir ${path}))
$(info basename = $(basename ${path}))
$(info suffix = $(suffix ${path}))

.PHONY: build
build:
