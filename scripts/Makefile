# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

include ../compiler/compiler.mk
include ../tlbuild.mk
include ../glibc/glibc.mk
include success.mk
include wow.mk
include logos.mk
include ../gnu/gnu.mk
include git.mk

CC := gcc

feature-m32 := $(findstring 1,$(call check_compiler_option,$(CC),-m32))
feature-sve2 := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+sve+sve2))
feature-avx2 := $(findstring 1,$(call check_compiler_option,$(CC),-mavx2))
feature-avx512 := $(findstring 1,$(call check_compiler_option,$(CC),-mavx512))
feature-lse := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+lse))
feature-fcf-protection1 := $(findstring 1,$(call check_compiler_option,$(CC),-fcf-protection))
feature-fcf-protection2 := $(findstring 1,$(call check_clang_option,-fcf-protection))

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

all: test_call

test_call:
	$(call success)
	$(call wow)
	$(call wow,PREFIX)
	$(call tl_ascii_logo1,===)
	$(call tl_ascii_logo_ebpf_bee_summit_2021)
	$(call tl_ascii_logo_gnu)
	$(call git_config)
	$(call git_archive)
	$(Q)./moonlight.sh
	$(Q)./gotoxy.sh
	@echo -e "  \033[1;33mDone\033[m"
test:

clean:
	@rm -f test-linux-*.tar.gz
