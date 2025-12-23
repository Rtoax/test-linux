# SPDX-License-Identifier: GPL-3.0
include arch.mk
include compiler.mk
include cpu.mk
include binutils.mk

OUTPUT := .output/

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
target-${IS_X86_64} += syscall
target-${IS_AARCH64} += mrs
target-y += breakpoint
target-y += ret
target-y += udiv div
target-y += simd
target-y += cpuid_user
target-y += invalid_opcode_user

ARCH_LIB_CPUID :=

CFLAGS += ${cpu-feature-cflags}

ifeq ($(shell uname -m),x86_64)
  ifneq ($(shell lscpu | grep -w avx2),)
    CFLAGS += -mavx2 -mfma
  endif
  ifneq ($(shell lscpu | grep -w avx512f),)
    CFLAGS += -mavx512f -mfma
  endif

  ARCH_LIB_CPUID += ${OUTPUT}cpuid-x86.o
else ifeq ($(shell uname -m),aarch64)
  # Check cpu flags
  ifneq ($(shell lscpu | grep -w sve),)
    CFLAGS += -march=armv8-a+sve
  endif
  ifneq ($(shell lscpu | grep -w sve2),)
    CFLAGS += -march=armv8-a+sve2
  endif

  CFLAGS += -DCPU_HAVE_NEON=1

  ARCH_LIB_CPUID += ${OUTPUT}cpuid-arm64.o
endif

ifdef BFD
  LDFLAGS += -fuse-ld=bfd
  $(info User linker bfd)
endif

# Get GNU assembler version
CFLAGS += -DBINUTILS_VERSION_MAJOR=${BINUTILS_VERSION_MAJOR}
CFLAGS += -DBINUTILS_VERSION_MINOR=${BINUTILS_VERSION_MINOR}

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
CFLAGS_syscall := -nostdlib
LDFLAGS_syscall := -nostdlib
LDFLAGS_invalid_opcode_user := -no-pie

include main.mk

add-x86: ${OUTPUT}add-x86.o
breakpoint: ${OUTPUT}breakpoint.o
bts: ${OUTPUT}bts.o
bswapl: ${OUTPUT}bswapl.o
invalid_opcode_user: ${OUTPUT}invalid_opcode_user.o
cpuid_user: ${OUTPUT}cpuid_user.o ${ARCH_LIB_CPUID}
_mm_clflush: ${OUTPUT}_mm_clflush.o
prefetch: ${OUTPUT}prefetch.o
rte_memcpy: ${OUTPUT}rte_memcpy.o
fsin: ${OUTPUT}fsin.o
udiv: ${OUTPUT}udiv.o
div: ${OUTPUT}div.o
vgetbv: ${OUTPUT}vgetbv.o
stosb: ${OUTPUT}stosb.o
memset: ${OUTPUT}memset.o
nop: ${OUTPUT}nop.o
rdmsr: ${OUTPUT}rdmsr.o
mrs: ${OUTPUT}mrs.o
ret: ${OUTPUT}ret.o
simd: ${OUTPUT}simd.o
rdrand: ${OUTPUT}rdrand.o
rdseed: ${OUTPUT}rdseed.o
syscall: ${OUTPUT}syscall.o
