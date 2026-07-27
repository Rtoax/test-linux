# SPDX-License-Identifier: GPL-3.0
include kernel.mk
include cross-compile.mk
include compiler.mk
include os.mk

target-y += align
target-y += alias
target-y += arch
target-y += arg
target-y += bit
target-y += likely
target-y += offsetof
target-y += container_of
target-y += __clang__
target-y += __nonnull
target-y += __restrict__
target-y += __func__
target-y += __linux__
target-y += __WORDSIZE
target-${CC_SUPPORT_m32} += __WORDSIZE-32
target-y += __TIME__
target-y += __VERSION__
target-y += __FILE__
target-y += machine
target-y += __ASSEMBLER__
target-y += ident
target-y += __GNUC__ __GNUC_PREREQ
target-y += __has_include
target-y += __user
target-y += __stringify
target-y += __STDC__
target-y += _XOPEN_SOURCE
target-y += _POSIX_SOURCE _POSIX_C_SOURCE
target-y += LINUX_VERSION_CODE
target-y += __GLIBC__ __GLIBC_MINOR__ __GLIBC_PREREQ
target-y += __GLIBC_USE
target-y += splice
target-y += os

target-${IS_X86_64} += __x86_64__
target-${IS_PPC64LE} += __powerpc64__
target-${CC_SUPPORT_m32} += __i386__
target-${IS_AARCH64} += __aarch64__
target-${IS_LOONGARCH64} += __loongarch64

target-cpp-y := __cplusplus __cplusplus-std98

prep-y := ${CC}-macros.h
prog-y := likely.sh

CFLAGS += ${KFLAGS}

CFLAGS___stringify := -DSTDBOOL_HDR=stdbool.h
CFLAGS___i386__ := -m32
LDFLAGS___i386__ := -m32
ifndef CROSS_COMPILE
  CFLAGS___x86_64__ := -m64
endif
CFLAGS___WORDSIZE-32 := -m32
LDFLAGS___WORDSIZE-32 := -m32
CFLAGS_machine := -Wno-error=deprecated -Wno-deprecated
CFLAGS___user := -Wno-error=attributes
CFLAGS___cplusplus-std98 := -std=c++98
CFLAGS_os += ${OS_CFLAGS}
