# SPDX-License-Identifier: GPL-3.0
target-y :=
target-y += helloworld
target-y += march-native
target-y += mbranch-protection

ifeq ($(shell uname -m),aarch64)
  target-y += march-armv8.3-a
endif

# FIXME: aarch64 seems like don't support -mfentry
ifeq ($(shell uname -m),x86_64)
  target-y += mfentry
endif

target-shell-y := info.sh

CC := gcc
CFLAGS :=

include ../../compiler/compiler.mk

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

include ../../template/main.mk


helloworld: helloworld.o
march-native: march-native.o
march-armv8.3-a: march-armv8.3-a.o
mbranch-protection: mbranch-protection.o
mfentry: mfentry.o
