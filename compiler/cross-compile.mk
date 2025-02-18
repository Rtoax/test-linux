# SPDX-License-Identifier: GPL-3.0
# This file need included after CC, LD, AS, etc. in Makefile

SYSROOT ?= /home/rongtao/rootfs-aarch64

# Cross compile
ifdef CROSS_COMPILE
  ifndef SYSROOT
    $(error "Must define SYSROOT if CROSS_COMPILE")
  endif
  ifeq (${SYSROOT},)
    $(error "SYSROOT=${SYSROOT} is not exist")
  endif

  ifneq ($(shell uname -m),aarch64)
    CC := aarch64-linux-gnu-gcc
    AS := aarch64-linux-gnu-as
    LD := aarch64-linux-gnu-ld
    # This root could be created by Docker Image Tar Archive, debootstrap, etc.
    # see: aarch64-linux-gnu-gcc -print-sysroot
    CFLAGS += --sysroot=${SYSROOT}
    RUN_PFX := qemu-aarch64 --sysroot=${SYSROOT}
  endif

  # TODO: Add more architecture

  # Check
  ifeq (${CC},)
    $(error "$(shell uname -m) is not support CROSS_COMPILE")
  endif
endif

$(info Define CROSS_COMPILE=1 when make)
