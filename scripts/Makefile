SHELL = bash

include check_compiler_option.mk

feature-sve2 := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+sve+sve2))
feature-avx2 := $(findstring 1,$(call check_compiler_option,$(CC),-mavx2))
feature-avx512 := $(findstring 1,$(call check_compiler_option,$(CC),-mavx512))

$(info feature-sve2 ${feature-sve2})
$(info feature-avx2 ${feature-avx2})
$(info feature-avx512 ${feature-avx512})

all:
	@echo -e "  \033[1;33mDone\033[m"
test:
clean:
