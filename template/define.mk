# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Functions:
# - check_file_and_def()
#
ifndef _DEFINE_MK
export _DEFINE_MK = 1

# $1 - file path, like: /usr/include/stdio.h
# $2 - definition name, like HAVE_STDIO_H=y
define check_file_and_def
$(if $(wildcard $(1)), \
  $(eval export $(2) = y); \
  $(if $(DEBUG),$(info Found $(1), defining $(2)=y));, \
  $(if $(DEBUG),$(info Not found $(1), not define $(2))); \
)
endef

$(call check_file_and_def,/usr/include/stdio.h,HAVE_STDIO_H)
$(call check_file_and_def,/usr/include/nonsence.h,HAVE_NONSENSE_H)

ifndef HAVE_STDIO_H
  $(error "Not define HAVE_STDIO_H")
endif
ifdef HAVE_NONSENSE_H
  $(error "Never found HAVE_NONSENSE_H")
endif

endif
