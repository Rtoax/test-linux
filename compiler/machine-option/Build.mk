# SPDX-License-Identifier: GPL-3.0
target-y += helloworld
target-y += march-native
target-y += mbranch-protection
target-${IS_AARCH64} += march-armv8.3-a
# FIXME: aarch64 seems like don't support -mfentry
target-${IS_X86_64} += mfentry

shell-y := info.sh

include compiler.mk

pac-ret := $(call compiler_support_option,$(CC),-mbranch-protection=pac-ret)
ifeq (${pac-ret},y)
  CFLAGS_mbranch-protection := -mbranch-protection=pac-ret
else
  $(warning "$(CC) not support -mbranch-protection=pac-ret, '${pac-ret}'")
endif

CFLAGS_march-armv8.3-a := -march=armv8.3-a
CFLAGS_mfentry := -pg -mfentry

# FIXME: HygonGenuine not support x86-64
ifneq ($(CPU_VENDOR_ID),HygonGenuine)
  CFLAGS_march-native := -march=native
else
  $(warning CPU Vendor ID: ${CPU_VENDOR_ID})
endif
