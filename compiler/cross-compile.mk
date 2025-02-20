# SPDX-License-Identifier: GPL-3.0
# This file need included after CC, LD, AS, etc. in Makefile

CC ?= gcc
AS ?= as
LD ?= ld
CFLAGS ?=
SYSROOT ?= /home/rongtao/rootfs-aarch64

# Cross compile
ifdef CROSS_COMPILE
  ifndef SYSROOT
    $(error "Must define SYSROOT if CROSS_COMPILE")
  endif
  ifeq (${SYSROOT},)
    $(error "SYSROOT=${SYSROOT} is not exist")
  endif

  CC := ${CROSS_COMPILE}gcc
  CXX := ${CROSS_COMPILE}g++
  AS := ${CROSS_COMPILE}as
  LD := ${CROSS_COMPILE}ld

  ifneq ($(shell uname -m),aarch64)
    RUN_PFX := qemu-aarch64 --sysroot=${SYSROOT}
  endif

  # TODO: Add more architecture

  # This root could be created by Docker Image Tar Archive, debootstrap, etc.
  # see: aarch64-linux-gnu-gcc -print-sysroot
  CFLAGS += --sysroot=${SYSROOT}
  CFLAGS += -DCROSS_COMPILE=1

  MAKEFLAGS += CROSS_COMPILE=${CROSS_COMPILE}

  # Check
  ifeq (${CC},)
    $(error "$(shell uname -m) is not support CROSS_COMPILE")
  endif

  $(info INFO: Enable CROSS_COMPILE=${CROSS_COMPILE})
else
  $(info INFO: Define CROSS_COMPILE=[Cross-build [GNU] C compiler] when make)
endif

