SHELL = bash

include check_compiler_option.mk
include success.mk
include wow.mk

feature-sve2 := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+sve+sve2))
feature-avx2 := $(findstring 1,$(call check_compiler_option,$(CC),-mavx2))
feature-avx512 := $(findstring 1,$(call check_compiler_option,$(CC),-mavx512))
feature-lse := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+lse))

$(info feature-sve2 ${feature-sve2})
$(info feature-avx2 ${feature-avx2})
$(info feature-avx512 ${feature-avx512})
$(info feature-lse ${feature-lse})

ifeq (${feature-sve2},1)
  $(info CPU support SVE2)
endif

all:
	$(call success)
	$(call wow)
	$(call wow,PERFIX)
	@echo -e "  \033[1;33mDone\033[m"
test:
clean:
