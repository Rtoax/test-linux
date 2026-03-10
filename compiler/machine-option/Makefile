# SPDX-License-Identifier: GPL-3.0
include arch.mk

target-y += helloworld
target-y += march-native
target-y += mbranch-protection
target-${IS_AARCH64} += march-armv8.3-a
# FIXME: aarch64 seems like don't support -mfentry
target-${IS_X86_64} += mfentry

target-shell-y := info.sh

CC := gcc

include compiler.mk

pac-ret := $(findstring 1,$(call check_compiler_option,$(CC),-mbranch-protection=pac-ret))

ifeq (${pac-ret},1)
  CFLAGS_mbranch-protection := -mbranch-protection=pac-ret
else
  $(warning "$(CC) not support -mbranch-protection=pac-ret")
endif

CFLAGS_march-armv8.3-a := -march=armv8.3-a
CFLAGS_mfentry := -pg -mfentry

# FIXME: HygonGenuine not support x86-64
ifneq ($(CPU_VENDOR_ID),HygonGenuine)
  CFLAGS_march-native := -march=native
else
  $(warning CPU Vendor ID: ${CPU_VENDOR_ID})
endif

include main.mk
