# SPDX-License-Identifier: GPL-3.0
include ../../template/arch.mk
include ../../compiler/compiler.mk
include ../../binutils/binutils.mk

subdir-y :=
subdir-${IS_X86_64} += avx
subdir-${IS_X86_64} += tsc
subdir-${IS_X86_64} += pku
subdir-${IS_X86_64} += sse
subdir-${IS_AARCH64} += neon
subdir-${IS_AARCH64} += sve

target-y :=
target-${IS_X86_64} += add-x86
target-${IS_X86_64} += bts
target-${IS_X86_64} += fsin
target-${IS_X86_64} += bswapl
target-${IS_X86_64} += _mm_clflush
target-${IS_X86_64} += prefetch
target-${IS_X86_64} += rte_memcpy
target-${IS_X86_64} += vgetbv
target-${IS_X86_64} += stosb memset
target-${IS_X86_64} += nop
target-${IS_X86_64} += rdmsr
target-${IS_X86_64} += rdrand
target-${IS_X86_64} += rdseed
target-${IS_AARCH64} += mrs
target-y += breakpoint
target-y += ret
target-y += udiv div
target-y += simd
target-y += cpuid_user
target-y += invalid_opcode_user

ARCH_LIB_CPUID :=

ifeq ($(shell uname -m),x86_64)
  ifneq ($(shell lscpu | grep -w avx2),)
    CFLAGS += -mavx2 -mfma
    CFLAGS += -DCPU_HAVE_AVX2=1
  endif
  ifneq ($(shell lscpu | grep -w avx512f),)
    CFLAGS += -mavx512f -mfma
    CFLAGS += -DCPU_HAVE_AVX512F=1
  endif

  ARCH_LIB_CPUID += cpuid-x86.o
else ifeq ($(shell uname -m),aarch64)
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

  ARCH_LIB_CPUID += cpuid-arm64.o
endif

ifdef BFD
  LDFLAGS += -fuse-ld=bfd
  $(info User linker bfd)
endif

# Get GNU assembler version
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
CFLAGS_simd := -Wno-error=uninitialized

ifdef IGNORE_RETURN_VALUE
  CFLAGS_udiv += -DIGNORE_RETURN_VALUE=1
  CFLAGS_div += -DIGNORE_RETURN_VALUE=1
endif

CFLAGS_ret := -Wno-error=return-type

include ../../template/main.mk

add-x86: add-x86.o
breakpoint: breakpoint.o
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
