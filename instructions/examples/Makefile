# SPDX-License-Identifier: GPL-3.0
sub-dir :=

TARGETS :=
CC := gcc
CFLAGS :=
LDFLAGS :=
ARCH_LIB_CPUID :=

ifeq ($(shell uname -m),x86_64)
  sub-dir += avx
  sub-dir += tsc
  sub-dir += pku
  sub-dir += sse

  ifneq ($(shell lscpu | grep -w avx2),)
    CFLAGS += -mavx2 -mfma
    CFLAGS += -DCPU_HAVE_AVX2=1
  endif
  ifneq ($(shell lscpu | grep -w avx512f),)
    CFLAGS += -mavx512f -mfma
    CFLAGS += -DCPU_HAVE_AVX512F=1
  endif
  TARGETS += add-x86
  TARGETS += bts
  TARGETS += fsin
  TARGETS += bswapl
  TARGETS += _mm_clflush
  TARGETS += prefetch
  TARGETS += rte_memcpy
  TARGETS += vgetbv
  TARGETS += stosb memset
  TARGETS += nop
  TARGETS += rdmsr
  ifneq ($(shell lscpu | grep -w rdrand),)
    TARGETS += rdrand
  endif
  ifneq ($(shell lscpu | grep -w rdseed),)
  TARGETS += rdseed
  endif

  ARCH_LIB_CPUID += cpuid-x86.o
else ifeq ($(shell uname -m),aarch64)
  sub-dir += neon
  sub-dir += sve

  # Check cpu flags
  ifneq ($(shell lscpu | grep -w sve),)
    CFLAGS += -DCPU_HAVE_SVE=1
    CFLAGS += -march=armv8-a+sve
  endif
  ifneq ($(shell lscpu | grep -w sve2),)
    CFLAGS += -DCPU_HAVE_SVE2=1
    CFLAGS += -march=armv8-a+sve2
  endif

  CFLAGS += -DCPU_HAVE_NEON=1
  TARGETS += mrs

  ARCH_LIB_CPUID += cpuid-arm64.o
endif

ifdef BFD
  LDFLAGS += -fuse-ld=bfd
  $(info User linker bfd)
endif

TARGETS += ret
TARGETS += udiv div
TARGETS += simd
TARGETS += cpuid_user
TARGETS += invalid_opcode_user

# Get GNU assembler version
include $(shell pwd)/../../binutils/binutils.mk
CFLAGS += -DBINUTILS_VERSION_MAJOR=${BINUTILS_VERSION_MAJOR}
CFLAGS += -DBINUTILS_VERSION_MINOR=${BINUTILS_VERSION_MINOR}

#CFLAGS +=
CFLAGS += -g -ggdb
CFLAGS += -O0
CFLAGS += -pthread

CFLAGS += -no-pie

CFLAGS_rdrand := -mrdrnd
CFLAGS_rdseed := -mrdseed
CFLAGS_udiv := -O0
CFLAGS_div := -O0
CFLAGS__mm_clflush := -DFLUSH

ifdef IGNORE_RETURN_VALUE
  CFLAGS_udiv += -DIGNORE_RETURN_VALUE=1
  CFLAGS_div += -DIGNORE_RETURN_VALUE=1
endif

CFLAGS_ret := -Wno-error=return-type

include ../../template/main.mk

add-x86: add-x86.o
bts: bts.o
bswapl: bswapl.o
invalid_opcode_user: invalid_opcode_user.o
cpuid_user: cpuid_user.o ${ARCH_LIB_CPUID}
_mm_clflush: _mm_clflush.o
prefetch: prefetch.o
rte_memcpy: rte_memcpy.o
fsin: fsin.o
udiv: udiv.o
div: div.o
vgetbv: vgetbv.o
stosb: stosb.o
memset: memset.o
nop: nop.o
rdmsr: rdmsr.o
mrs: mrs.o
ret: ret.o
simd: simd.o
rdrand: rdrand.o
rdseed: rdseed.o
