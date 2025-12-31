# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Functions:
# - check_file_and_def()
#
_DEFINE_MK = 1

# $1 - file path, like: /usr/include/stdio.h
# $2 - definition name, like HAVE_STDIO
define check_file_and_def
$(if $(wildcard $(1)), \
  $(eval export $(2) = y); \
  $(if $(DEBUG),$(info Found $(1), defining $(2)));, \
  $(if $(DEBUG),$(info Not found $(1), not define $(2))); \
)
endef

$(call check_file_and_def,/usr/include/stdio.h,HAVE_STDIO_H)
$(call check_file_and_def,/usr/include/notexist.h,HAVE_NOTEXIST)

ifndef HAVE_STDIO_H
  $(error "Not define HAVE_STDIO_H")
endif
ifdef HAVE_NOTEXIST
  $(error "Never found HAVE_NOTEXIST")
endif
