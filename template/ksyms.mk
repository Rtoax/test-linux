# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - KALLSYMS=[/proc/kallsyms]
#
# Functions:
# - ksyms_have_func()=[y]
#
ifndef _KSYMS_MK
_KSYMS_MK = 1

include shell.mk
include sudo.mk

KALLSYMS := /proc/kallsyms

# Check kernel func
# $1: function name, like 'schedule'
#
# @return: echo 'y' if found
define ksyms_have_func
$(shell \
  cat ${KALLSYMS} | \
    awk -v kfunc="${1}" '{ \
      if ($$2=="t" || $$2=="T") { \
        if ($$3 == kfunc) {print "y"} \
      } \
    }' \
)
endef

ifdef DEBUG
  $(info KALLSYMS = ${KALLSYMS})
endif

ifneq ($(call ksyms_have_func,schedule),y)
  $(error Not found function schedule from ${KALLSYMS})
endif

endif # end of _KSYMS_MK
