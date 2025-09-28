# SPDX-License-Identifier: GPL-3.0
_COMPILER = 1

SHELL := bash

CC ?= gcc
CXX ?= c++
CLANG ?= clang
GCC ?= gcc

# Check compiler support option or not
# $(1) - compiler, for example: gcc, clang, etc.
# $(2) - compile option, for example: -flto
define check_compiler_option
  $(shell echo 'int main(void) { return 0; }' | \
    $(1) -x c -Wall - $(2) -S -o /dev/null >/dev/null 2>&1 \
      && echo 1)
endef

define check_compiler_option_noS
  $(shell echo 'int main(void) { return 0; }' | \
    $(1) -x c -Wall - $(2) -o /dev/null >/dev/null 2>&1 \
      && echo 1)
endef

# Check compiler support type
# $(1) - compiler, gcc, clang, etc.
# $(2) - type name, such as _Float16, float, etc.
define check_compiler_support_type
$(shell echo 'int main(void) { $(2) v; return 0; }' | \
	$(1) -x c -Werror - -o /dev/null 2>/dev/null && echo y)
endef

define check_clang_option
	$(call check_compiler_option,clang,$(1))
endef

define check_gcc_option
	$(call check_compiler_option,gcc,$(1))
endef

ifndef CROSS_COMPILE
  MARCH_NATIVE := -march=native
endif
# $(1) - compiler, CC or CXX
# $(2) - output file name
define __gen_compiler_macro_hdr
	$(1) ${MARCH_NATIVE} -E -dM - </dev/null -o $(2)
endef

# $(1) - output file name
define gen_compiler_macro_hdr
$(call __gen_compiler_macro_hdr,$(CC),$(1))
endef

CC_M32 := $(findstring 1,$(call check_compiler_option_noS,$(CC),-m32))
CC_STD_GNU11 := $(findstring 1,$(call check_compiler_option,$(CC),-std=gnu11))
CC_STD_GNU17 := $(findstring 1,$(call check_compiler_option,$(CC),-std=gnu17))
CC_STD_GNU++20 := $(findstring 1,$(call check_compiler_option,$(CC),-std=gnu++20))
CC_STD_C++20 := $(findstring 1,$(call check_compiler_option,$(CC),-std=c++20))

# see https://clang.llvm.org/docs/LanguageExtensions.html
CC__Float32 := $(findstring y,$(call check_compiler_support_type,$(CC),_Float16))

CC_FULLVERSION := $(shell $(CC) -dumpfullversion -dumpversion)
CC_VERSION := $(shell $(CC) -dumpversion)
CC_MAJOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$1}')
CC_MINOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$2}')

CC_-fcf-protection := $(findstring 1,$(call check_compiler_option,$(CC),-fcf-protection))
CC_-fpatchable-function-entry := $(findstring 1,$(call check_compiler_option,$(CC),-fpatchable-function-entry=5,2))
CC_-mfentry := $(findstring 1,$(call check_compiler_option,$(CC),-mfentry))

feature-m32 := $(findstring 1,$(call check_compiler_option,$(CC),-m32))
feature-sve2 := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+sve+sve2))
feature-avx2 := $(findstring 1,$(call check_compiler_option,$(CC),-mavx2))
feature-avx512 := $(findstring 1,$(call check_compiler_option,$(CC),-mavx512))
feature-lse := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+lse))
feature-fcf-protection1 := $(findstring 1,$(call check_compiler_option,$(CC),-fcf-protection))
feature-fcf-protection2 := $(findstring 1,$(call check_clang_option,-fcf-protection))

ifdef DEBUG
  $(info fcf-protection: ${CC_-fcf-protection})
  $(info fentry: $(CC_-mfentry))
  $(info CC: $(CC) ${CC_MAJOR}.${CC_MINOR} ${CC_FULLVERSION} ${CC_VERSION})
  $(info CC_M32: ${CC_M32})
  $(info CC_STD_GNU11: ${CC_STD_GNU11})
  $(info CC_STD_GNU17: ${CC_STD_GNU17})
  $(info CC_STD_GNU++20: ${CC_STD_GNU++20})
  $(info CC_STD_C++20: ${CC_STD_C++20})
  $(info CC__Float32: ${CC__Float32})

  $(info feature-m32 ${feature-m32})
  $(info feature-sve2 ${feature-sve2})
  $(info feature-avx2 ${feature-avx2})
  $(info feature-avx512 ${feature-avx512})
  $(info feature-lse ${feature-lse})
  $(info feature-fcf-protection1 ${feature-fcf-protection1})
  $(info feature-fcf-protection2 ${feature-fcf-protection2})

  ifeq (${feature-sve2},1)
    $(info CPU support SVE2)
  endif
endif
