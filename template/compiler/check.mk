# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
# - CC=[cc]
#
# Functions:
# - compiler_support_option()=[y]
# - check_clang_option()=[y]
# - check_gcc_option()=[y]
# - compiler_support_type()=[y]
# - compiler_support_header()=[y]
#
ifndef _COMPILER_CHECK_MK
_COMPILER_CHECK_MK = 1

# Check compiler support option or not
# $(1) - compiler, for example: gcc, clang, etc.
# $(2) - compile option, for example: -flto, -m32
define compiler_support_option
$(shell printf 'int main(void) { return 0; }' | \
  $(1) -x c -Wall - -c $(2) -o /dev/null >/dev/null 2>&1 \
    && echo y)
endef
define check_clang_option
$(call compiler_support_option,clang,$(1))
endef
define check_gcc_option
$(call compiler_support_option,gcc,$(1))
endef

# Check compiler support type
# $(1) - compiler, gcc, clang, etc.
# $(2) - type name, such as _Float16, float, etc.
define compiler_support_type
$(shell printf 'int main(void) { $(2) v; return 0; }' | \
	$(1) -x c -Werror - -o /dev/null 2>/dev/null && echo y)
endef

# Check compiler have header
# $(1) - compiler, gcc, clang, etc.
# $(2) - header name, like quadmath.h
define compiler_support_header
$(shell printf '#include <$(2)>\nint main(void) { return 0; }' | \
	$(1) -x c -Werror - -o /dev/null 2>/dev/null && echo y)
endef

ifneq ($(call compiler_support_option,${CC},),y)
  $(error compiler_support_option failed)
endif

ifneq ($(call compiler_support_type,${CC},int),y)
  $(error "${CC} not support int type!!")
endif

ifneq ($(call compiler_support_header,${CC},stdio.h),y)
  $(error compiler_support_header failed)
endif

endif
