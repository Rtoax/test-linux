# SPDX-License-Identifier: GPL-3.0
# Export:
# cflags-support-types-y
# cflags-support-headers-y
# ldflags-support-headers-y
#
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

CC_M32 := $(findstring y,$(call check_compiler_option_noS,$(CC),-m32))
CC_STD_GNU11 := $(findstring y,$(call check_compiler_option,$(CC),-std=gnu11))
CC_STD_GNU17 := $(findstring y,$(call check_compiler_option,$(CC),-std=gnu17))
CC_STD_GNU++20 := $(findstring y,$(call check_compiler_option,$(CC),-std=gnu++20))
CC_STD_C++20 := $(findstring y,$(call check_compiler_option,$(CC),-std=c++20))

# see https://clang.llvm.org/docs/LanguageExtensions.html
CC__Float16 := $(findstring y,$(call check_compiler_support_type,$(CC),_Float16))
CC___fp16 := $(findstring y,$(call check_compiler_support_type,$(CC),__fp16))
CC___bf16 := $(findstring y,$(call check_compiler_support_type,$(CC),__bf16))
# GCC Additional Floating Types: https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html
# - NVRTC on Linux
# - GCC version 4.1 or later on x86_64/amd64
# - Clang version 3.9 or later on x86_64/amd64
# - NVHPC version 21.1 or later on x86_64/amd64
CC___float128 := $(findstring y,$(call check_compiler_support_type,$(CC),__float128))
CC__Float128 := $(findstring y,$(call check_compiler_support_type,$(CC),_Float128))
CC___float80 := $(findstring y,$(call check_compiler_support_type,$(CC),__float80))
CC___uint128_t := $(findstring y,$(call check_compiler_support_type,$(CC),__uint128_t))

CC_H_quadmath_h := $(findstring y,$(call check_compiler_support_header,$(CC),quadmath.h))

cflags-support-types-y :=
cflags-support-types-${CC__Float16} += -DSUPPORT__Float16=1
cflags-support-types-${CC___fp16} += -DSUPPORT___fp16=1
cflags-support-types-${CC___bf16} += -DSUPPORT___bf16=1
cflags-support-types-${CC___float128} += -DSUPPORT___float128=1
cflags-support-types-${CC__Float128} += -DSUPPORT__Float128=1
cflags-support-types-${CC___float80} += -DSUPPORT___float80=1
cflags-support-types-${CC___uint128_t} += -DSUPPORT___uint128_t=1

cflags-support-headers-y :=
cflags-support-headers-${CC_H_quadmath_h} += -DSUPPORT_quadmath_h=1
ldflags-support-headers-y :=
ldflags-support-headers-${CC_H_quadmath_h} += -lquadmath

CC_FULLVERSION := $(shell $(CC) -dumpfullversion -dumpversion)
CC_VERSION := $(shell $(CC) -dumpversion)
CC_MAJOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$1}')
CC_MINOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$2}')

CC_-fcf-protection := $(findstring y,$(call check_compiler_option,$(CC),-fcf-protection))
CC_-fpatchable-function-entry := $(findstring y,$(call check_compiler_option,$(CC),-fpatchable-function-entry=5,2))
CC_-mfentry := $(findstring y,$(call check_compiler_option,$(CC),-mfentry))
CC_-mavx2 := $(findstring y,$(call check_compiler_option,$(CC),-mavx2))

feature-m32 := $(findstring y,$(call check_compiler_option,$(CC),-m32))
feature-sve2 := $(findstring y,$(call check_compiler_option,$(CC),-march=armv8-a+sve+sve2))
feature-avx512 := $(findstring y,$(call check_compiler_option,$(CC),-mavx512))
feature-lse := $(findstring y,$(call check_compiler_option,$(CC),-march=armv8-a+lse))
feature-fcf-protection1 := $(findstring y,$(call check_compiler_option,$(CC),-fcf-protection))
feature-fcf-protection2 := $(findstring y,$(call check_clang_option,-fcf-protection))

ifdef DEBUG
  $(info fcf-protection: ${CC_-fcf-protection})
  $(info fentry: $(CC_-mfentry))
  $(info CC: $(CC) ${CC_MAJOR}.${CC_MINOR} ${CC_FULLVERSION} ${CC_VERSION})
  $(info CC_M32: ${CC_M32})
  $(info CC_STD_GNU11: ${CC_STD_GNU11})
  $(info CC_STD_GNU17: ${CC_STD_GNU17})
  $(info CC_STD_GNU++20: ${CC_STD_GNU++20})
  $(info CC_STD_C++20: ${CC_STD_C++20})
  $(info CC_-mavx2 ${CC_-mavx2})
  $(info CC__Float16: ${CC__Float16})
  $(info CC___fp16: ${CC___fp16})
  $(info CC___bf16: ${CC___bf16})
  $(info CC___float128: ${CC___float128})
  $(info CC__Float128: ${CC__Float128})
  $(info CC___float80: ${CC___float80})
  $(info CC___uint128_t: ${CC___uint128_t})
  $(info cflags-support-types-y: ${cflags-support-types-y})
  $(info cflags-support-headers-y: ${cflags-support-headers-y})
  $(info ldflags-support-headers-y: ${ldflags-support-headers-y})

  $(info feature-m32 ${feature-m32})
  $(info feature-sve2 ${feature-sve2})
  $(info feature-avx512 ${feature-avx512})
  $(info feature-lse ${feature-lse})
  $(info feature-fcf-protection1 ${feature-fcf-protection1})
  $(info feature-fcf-protection2 ${feature-fcf-protection2})

  $(info CC_H_quadmath_h ${CC_H_quadmath_h})
endif
