# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Functions:
# - check_file_and_def()=[y]
# - find_cmd_and_def()=[y|n]
#
ifndef _DEFINE_MK
_DEFINE_MK = 1

include string.mk

# $1 - file path, like: /usr/include/stdio.h
# $2 - definition name, like HAVE_STDIO_H=y
define check_file_and_def
$(if $(wildcard $(1)), \
  $(eval export $(2) = y); \
  $(if $(DEBUG),$(info Found $(1), define $(2)=y));, \
  $(if $(DEBUG),$(info Not found $(1), do not define $(2))); \
)
endef

# Find command in env and define CMD=[/path/to/cmd] and HAVE_CMD=[y|n]
# $1: command name, like qemu-nbd
# $2: alias name, for example, if $1=clang++, $2 could be clangxx
define find_cmd_and_def
$(if ${2},$(eval __Name := $(call underscore_non_alnum,$(call toupper_shell,${2}))))
$(eval __Name ?= $(call underscore_non_alnum,$(call toupper_shell,${1})))
$(eval ${__Name} := $(shell which ${1} 2>/dev/null | grep -v ^alias))
$(if ${${__Name}}, \
  $(eval export HAVE_${__Name} := y), \
  $(eval export HAVE_${__Name} := n) \
)
$(if ${DEBUG}, $(info ${__Name} = ${${__Name}}))
$(if ${DEBUG}, $(info HAVE_${__Name} = ${HAVE_${__Name}}))
endef

# Do some checks
$(call check_file_and_def,/usr/include/stdio.h,HAVE_STDIO_H)
$(call check_file_and_def,/usr/include/nonsence.h,HAVE_NONSENSE_H)
ifndef HAVE_STDIO_H
  $(error "Not define HAVE_STDIO_H")
endif
ifdef HAVE_NONSENSE_H
  $(error "Never found HAVE_NONSENSE_H")
endif

$(call find_cmd_and_def,ls)
ifneq (${HAVE_LS},y)
  $(error find_cmd_and_def ls failed)
endif
$(call find_cmd_and_def,abc++,abcxx)
ifneq (${HAVE_ABCXX},n)
  $(error find_cmd_and_def abcxx failed, )
endif

endif
