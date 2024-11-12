# SPDX-License-Identifier: GPL-3.0

# Check compiler support option or not
# $(1) - compiler, for example: gcc, clang, etc.
# $(2) - compile option, for example: -flto
define check_compiler_option
  $(shell echo 'int main(void) { return 0; }' | \
    $(1) -x c -Wall - $(2) -S -o /dev/null >/dev/null 2>&1 \
      && echo 1)
endef

define check_clang_option
	$(call check_compiler_option,clang,$(1))
endef

define check_gcc_option
	$(call check_compiler_option,gcc,$(1))
endef
