# SPDX-License-Identifier: GPL-3.0

define func_foo
$(shell touch vmlinux.h)
endef

define func_bar
$(call func_foo)$(shell echo y)
endef

flag-1 := $(call func_bar)
$(info <${flag-1}>)

.PHONY: build
build:
