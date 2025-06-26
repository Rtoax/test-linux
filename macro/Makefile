# SPDX-License-Identifier: GPL-3.0
include ../kernel.mk
include ../compiler/cross-compile.mk
include ../compiler/compiler.mk

TARGETS :=
TARGETS += align
TARGETS += alias
TARGETS += arch
TARGETS += bit
TARGETS += likely
TARGETS += offsetof
TARGETS += container_of
TARGETS += __clang__
TARGETS += __nonnull
TARGETS += __restrict__
TARGETS += __func__
TARGETS += __linux__
TARGETS += __WORDSIZE
ifeq ($(CC_M32),1)
  TARGETS += __WORDSIZE-32
endif
TARGETS += __TIME__
TARGETS += __VERSION__
TARGETS += __FILE__
TARGETS += machine
TARGETS += __ASSEMBLER__
TARGETS += ident
TARGETS += __GNUC__ __GNUC_PREREQ
TARGETS += __has_include
TARGETS += __user
TARGETS += __stringify
TARGETS += __STDC__
TARGETS += _XOPEN_SOURCE
TARGETS += _POSIX_SOURCE _POSIX_C_SOURCE
TARGETS += LINUX_VERSION_CODE
TARGETS += __GLIBC__ __GLIBC_MINOR__ __GLIBC_PREREQ

TARGETS_CXX :=
TARGETS_CXX += __cplusplus __cplusplus-std98

ifeq ($(shell uname -m),x86_64)
  TARGETS += __x86_64__
ifeq ($(CC_M32),1)
  TARGETS += __i386__
endif
endif
ifeq ($(shell uname -m),aarch64)
  TARGETS += __aarch64__
endif
ifeq ($(shell uname -m),sw_64)
endif
ifeq ($(shell uname -m),loongarch64)
  TARGETS += __loongarch64
endif

CFLAGS += ${KFLAGS}

ifdef STATIC
  LDFLAGS += -static
endif

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

TARGETS_PREP := compiler-macros.h
TARGETS_SHELL := likely.sh

include ../template/main.mk

arch: arch.o
align: align.o
alias: alias.o
alias.o: alias.h
bit: bit.o
likely: likely.o
offsetof: offsetof.o
offsetof.o: offsetof.h
container_of: container_of.o
__clang__: __clang__.o
__i386__: __i386__.o
__x86_64__: __x86_64__.o
__aarch64__: __aarch64__.o
__loongarch64: __loongarch64.o
__nonnull: __nonnull.o
__cplusplus: __cplusplus.cpp.o
__cplusplus-std98: __cplusplus-std98.cpp.o
__restrict__: __restrict__.o
__func__: __func__.o
__linux__: __linux__.o
__WORDSIZE: __WORDSIZE.o
__WORDSIZE-32: __WORDSIZE-32.o
__TIME__: __TIME__.o
__VERSION__: __VERSION__.o
__FILE__: __FILE__.o
machine: machine.o
__ASSEMBLER__: __ASSEMBLER__.o
ident: ident.o
__GNUC__: __GNUC__.o
__GNUC_PREREQ: __GNUC_PREREQ.o
__has_include: __has_include.o
__user: __user.o
__stringify: __stringify.o
__STDC__: __STDC__.o
_XOPEN_SOURCE: _XOPEN_SOURCE.o
_POSIX_SOURCE: _POSIX_SOURCE.o
_POSIX_C_SOURCE: _POSIX_C_SOURCE.o
LINUX_VERSION_CODE: LINUX_VERSION_CODE.o
__GLIBC__: __GLIBC__.o
__GLIBC_MINOR__: __GLIBC_MINOR__.o
__GLIBC_PREREQ: __GLIBC_PREREQ.o

compiler-macros.h:
	@echo -e "  GEN ${CC} MACRO HDR \033[1m$(@)\033[m"
	$(call gen_compiler_macro_hdr,$(@))
