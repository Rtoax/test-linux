# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2023-2026 Rong Tao. All rights reserved.
include kconfig.mk
include helpers.mk
include cestc/lingspeed.mk
include cestc/luca.mk
include nvidia/cuda.mk
include nvidia/device.mk

subdir-y += aslr
subdir-y += cma
subdir-y += e820
subdir-y += rss
subdir-y += cache
subdir-y += hugepage
subdir-y += oom
subdir-y += tcmalloc
subdir-y += tlb
subdir-y += jemalloc
subdir-y += vma
subdir-y += vmalloc
subdir-y += pmem

target-y := virt2phy
target-liba-y := libtest-linux-mm.a

virt2phy-deps := numa.a.1
virt2phy-objs := ${PROC_HELPERS} ${MMAP_HELPERS}

libtest-linux-mm.a-objs := virt2phy.a.o

CFLAGS_virt2phy := -DHAVE_MAIN=1
CFLAGS_virt2phy += -DHAVE_LIB_TEST_LINUX_C=1
CFLAGS_virt2phy += -DHAVE_LIB_TEST_LINUX_NUMA=1
CFLAGS_virt2phy += -DHAVE_MMAP_HELPERS=1
CFLAGS_virt2phy += -I../numa/
LDFLAGS_virt2phy += -lnuma

ifeq ($(CONFIG_DEVMEM),y)
  $(info CONFIG_DEVMEM=y)
  CFLAGS_virt2phy += -DCONFIG_DEVMEM=1
endif
# CONFIG_STRICT_DEVMEM=y is the default kernel configuration in general,
# disallows to access RAM area via /dev/mem or only allows first 1MB size
# of RAM.
ifeq ($(CONFIG_STRICT_DEVMEM),y)
  $(warning CONFIG_STRICT_DEVMEM=y, you don not allow r/w from/to /dev/mem)
  CFLAGS_virt2phy += -DCONFIG_STRICT_DEVMEM=1
endif
ifeq ($(CONFIG_MEMFD_CREATE),y)
  $(info CONFIG_MEMFD_CREATE=y)
  CFLAGS_virt2phy += -DCONFIG_MEMFD_CREATE=1
endif

# Compile CUDA virt2phy
ifeq (${HAVE_CUDA}${HAVE_NVIDIA_GPU},yy)
  target-nvcc-y := virt2phy-nv
  virt2phy-nv-deps := numa.so
  virt2phy-nv-objs := ${PROC_HELPERS} ${MMAP_HELPERS} virt2phy.cu.o
  CFLAGS_NVCC_virt2phy := ${CFLAGS_virt2phy}
  LDFLAGS_NVCC_virt2phy-nv := ${LDFLAGS_virt2phy}
  LDFLAGS_NVCC_virt2phy-nv += -Xlinker -rpath -Xlinker ${TOPDIR}/libs
  LDFLAGS_NVCC_virt2phy-nv += -Xlinker -rpath -Xlinker ${TOPDIR}/numa
endif
ifeq (${HAVE_LUCA}${HAVE_LINGSPEED_GPU},yy)
  target-lscc-y := virt2phy-luca
  virt2phy-luca-deps := numa.so
  virt2phy-luca-objs := ${PROC_HELPERS} ${MMAP_HELPERS} virt2phy.luca.o
  CFLAGS_LSCC_virt2phy := ${CFLAGS_virt2phy}
  LDFLAGS_LSCC_virt2phy-luca := ${LDFLAGS_virt2phy}
  LDFLAGS_LSCC_virt2phy-luca += -Xlinker -rpath -Xlinker ${TOPDIR}/libs
  LDFLAGS_LSCC_virt2phy-luca += -Xlinker -rpath -Xlinker ${TOPDIR}/numa
endif
