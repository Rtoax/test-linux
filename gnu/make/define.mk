# SPDX-License-Identifier: GPL-3.0

define func_foo
$(shell touch vmlinux.h)
endef

define func_bar
$(call func_foo)$(shell echo y)
endef

define local_var
$(shell echo $(shell dirname ${1}) .. $(shell basename ${1}))
endef

flag-1 := $(call func_bar)
$(info flag-1 = <${flag-1}>)

flag-2 := $(call local_var,/home/rongtao)
$(info flag-2 = <${flag-2}>)

.PHONY: build
build:
