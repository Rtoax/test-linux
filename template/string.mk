# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Functions:
# - toupper()
# - toupper_shell()
# - tolower()
# - tolower_shell()
#
ifndef _STRING_MK
_STRING_MK = 1

define toupper
echo $(1) | tr '[:lower:]' '[:upper:]'
endef
define toupper_shell
$(shell $(call toupper,${1}))
endef

define tolower
echo $(1) | tr '[:upper:]' '[:lower:]'
endef
define tolower_shell
$(shell $(call tolower,${1}))
endef

ifneq ($(call toupper_shell,abcDEF),ABCDEF)
  $(error "ERROR: toupper failed, $(call toupper_shell,abcDEF)")
endif
ifneq ($(call tolower_shell,abcDEF),abcdef)
  $(error "ERROR: toupper failed, $(call tolower_shell,abcDEF)")
endif

endif
