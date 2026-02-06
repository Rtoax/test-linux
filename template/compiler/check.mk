# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
# - CC=[cc]
#
ifndef _COMPILER_CHECK_MK
_COMPILER_CHECK_MK = 1

# Check compiler support option or not
# $(1) - compiler, for example: gcc, clang, etc.
# $(2) - compile option, for example: -flto
define check_compiler_option
  $(shell echo 'int main(void) { return 0; }' | \
    $(1) -x c -Wall - $(2) -S -o /dev/null >/dev/null 2>&1 \
      && echo y)
endef

define check_compiler_option_noS
  $(shell echo 'int main(void) { return 0; }' | \
    $(1) -x c -Wall - $(2) -o /dev/null >/dev/null 2>&1 \
      && echo y)
endef

# Check compiler support type
# $(1) - compiler, gcc, clang, etc.
# $(2) - type name, such as _Float16, float, etc.
define check_compiler_support_type
$(shell echo 'int main(void) { $(2) v; return 0; }' | \
	$(1) -x c -Werror - -o /dev/null 2>/dev/null && echo y)
endef

# Check compiler have header
# $(1) - compiler, gcc, clang, etc.
# $(2) - header name, like quadmath.h
define check_compiler_support_header
$(shell echo -e '#include <$(2)> \nint main(void) { return 0; }' | \
	$(1) -x c -Werror - -o /dev/null 2>/dev/null && echo y)
endef

define check_clang_option
$(call check_compiler_option,clang,$(1))
endef

define check_gcc_option
$(call check_compiler_option,gcc,$(1))
endef

ifneq ($(call check_compiler_support_type,int),y)
  $(error "${CC} not support int type!!")
endif
