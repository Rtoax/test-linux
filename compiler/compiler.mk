# SPDX-License-Identifier: GPL-3.0
SHELL := bash

CC ?= gcc

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

define check_clang_option
	$(call check_compiler_option,clang,$(1))
endef

define check_gcc_option
	$(call check_compiler_option,gcc,$(1))
endef

# $(1) - output file name
define gen_compiler_macro_hdr
	$(CC) -march=native -E -dM - </dev/null -o $(1)
endef

CC_M32 := $(findstring 1,$(call check_compiler_option_noS,$(CC),-m32))
CC_STD_GNU11 := $(findstring 1,$(call check_compiler_option,$(CC),-std=gnu11))
CC_STD_GNU17 := $(findstring 1,$(call check_compiler_option,$(CC),-std=gnu17))

CC_FULLVERSION := $(shell $(CC) -dumpfullversion -dumpversion)
CC_VERSION := $(shell $(CC) -dumpversion)
CC_MAJOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$1}')
CC_MINOR := $(shell echo ${CC_FULLVERSION} | awk -F '.' '{print $$2}')

CC_-fcf-protection := $(findstring 1,$(call check_compiler_option,$(CC),-fcf-protection))
CC_-fpatchable-function-entry := $(findstring 1,$(call check_compiler_option,$(CC),-fpatchable-function-entry=5,2))
CC_-mfentry := $(findstring 1,$(call check_compiler_option,$(CC),-mfentry))

ifdef DEBUG
  $(info fcf-protection: ${CC_-fcf-protection})
  $(info fentry: $(CC_-mfentry))
  $(info CC: $(CC) ${CC_MAJOR}.${CC_MINOR} ${CC_FULLVERSION} ${CC_VERSION})
endif
