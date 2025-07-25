# SPDX-License-Identifier: GPL-3.0
include ../kernel.mk
include ../compiler/cross-compile.mk
include ../compiler/compiler.mk

targets :=
targets += align
targets += alias
targets += arch
targets += bit
targets += likely
targets += offsetof
targets += container_of
targets += __clang__
targets += __nonnull
targets += __restrict__
targets += __func__
targets += __linux__
targets += __WORDSIZE
ifeq ($(CC_M32),1)
  targets += __WORDSIZE-32
endif
targets += __TIME__
targets += __VERSION__
targets += __FILE__
targets += machine
targets += __ASSEMBLER__
targets += ident
targets += __GNUC__ __GNUC_PREREQ
targets += __has_include
targets += __user
targets += __stringify
targets += __STDC__
targets += _XOPEN_SOURCE
targets += _POSIX_SOURCE _POSIX_C_SOURCE
targets += LINUX_VERSION_CODE
targets += __GLIBC__ __GLIBC_MINOR__ __GLIBC_PREREQ

targets-cpp :=
targets-cpp += __cplusplus __cplusplus-std98

ifeq ($(shell uname -m),x86_64)
  targets += __x86_64__
ifeq ($(CC_M32),1)
  targets += __i386__
endif
endif
ifeq ($(shell uname -m),aarch64)
  targets += __aarch64__
endif
ifeq ($(shell uname -m),sw_64)
endif
ifeq ($(shell uname -m),loongarch64)
  targets += __loongarch64
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

targets-prep := compiler-macros.h
targets-shell := likely.sh

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
	$(call log_tgt_obj,HDR,,$(@))
	$(call gen_compiler_macro_hdr,$(@))
