# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
_STRING = 1

define toupper
echo $(1) | tr '[:lower:]' '[:upper:]'
endef
define toupper_shell
$(shell $(call toupper,${1}))
endef

define tolower
$(shell echo $(1) | tr '[:upper:]' '[:lower:]')
endef

ifneq ($(call toupper_shell,abc),ABC)
  $(error "ERROR: toupper failed, $(call toupper_shell,abc)")
endif
