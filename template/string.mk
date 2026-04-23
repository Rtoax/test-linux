# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Functions:
# - toupper()
# - toupper_shell()
# - tolower()
# - tolower_shell()
# - uniq_repeat()
# - strip_tail()
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

# This is a good choice if a Makefile target has multiple conditional
# statements, for example:
# target-$(call uniq_repeat,${IS_AARCH64}$(call gcc_ge,15.2.1)) := x
#
# $1: string to uniq
# result: uniq string, for example: xxxyyy -> xy
define uniq_repeat
$(shell printf '%s' '$(subst ','\'',$(1))' | sed 's/\(.\)\1*/\1/g')
endef

# Strip a string in the end of string, like strip '-hip' from 'hello-hip'
# $1: string to strip
# $2: tail string
define strip_tail
$(shell echo ${1} | sed "s|${2}$$||g")
endef

ifneq ($(call toupper_shell,abcDEFgh),ABCDEFGH)
  $(error "ERROR: toupper failed, $(call toupper_shell,abcDEFgh)")
endif
ifneq ($(call tolower_shell,abcDEFgh),abcdefgh)
  $(error "ERROR: toupper failed, $(call tolower_shell,abcDEFgh)")
endif
ifneq ($(call uniq_repeat,xxxxxxxxxxxxxx),x)
  $(error "ERROR: uniq_repeat(xxxxxxxxxxxxxx) failed")
endif
ifneq ($(call uniq_repeat,yyyyyyyyyyyyyyy),y)
  $(error "ERROR: uniq_repeat(yyyyyyyyyyyyyyy) failed")
endif
ifneq ($(call uniq_repeat,xxxyyy),xy)
  $(error "ERROR: uniq_repeat(xxxyyy) failed")
endif
ifneq ($(call uniq_repeat,xxxyyyxxx),xyx)
  $(error "ERROR: uniq_repeat(xxxyyyxxx) failed")
endif
ifneq ($(call uniq_repeat,xyzzzzzzz),xyz)
  $(error "ERROR: uniq_repeat(xyzzzzzzz) failed")
endif
ifneq ($(call uniq_repeat,'''zzzzzzz),'z)
  $(error "ERROR: uniq_repeat('''zzzzzzz) failed")
endif
ifneq ($(call uniq_repeat,"""zzzzzzz),"z)
  $(error "ERROR: uniq_repeat("""zzzzzzz) failed")
endif
ifneq ($(call strip_tail,hello-hip,-hip),hello)
  $(error "ERROR: strip_tail(hello-hip, -hip) failed")
endif
ifneq ($(call strip_tail,hello-hip-x,-hip),hello-hip-x)
  $(error "ERROR: strip_tail(hello-hip-x, -hip) failed")
endif

endif
