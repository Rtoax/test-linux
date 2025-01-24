# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

CC = gcc
CXX = c++

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
TARGETS += __GNUC__
TARGETS += __has_include
TARGETS += __user
TARGETS += __stringify
TARGETS += __STDC__
TARGETS += _XOPEN_SOURCE
TARGETS += _POSIX_SOURCE _POSIX_C_SOURCE
TARGETS += LINUX_VERSION_CODE

TARGETS_CXX :=
TARGETS_CXX += __cplusplus

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

CFLAGS := -Werror -Wall
CFLAGS += -O0
CFLAGS += -DDEBUG -g

CFLAGS___stringify := -DSTDBOOL_HDR=stdbool.h

.PHONY: build
build: $(CC)-macros.h compiler-macros.h ${TARGETS} ${TARGETS_CXX}
	@echo -e " \033[1;33m Done \033[m"

arch: arch.o
align: align.o
alias: alias.o
bit: bit.o
likely: likely.o
offsetof: offsetof.o
container_of: container_of.o
__clang__: __clang__.o
__i386__: __i386__.o
__x86_64__: __x86_64__.o
__aarch64__: __aarch64__.o
__nonnull: __nonnull.o
__cplusplus: __cplusplus.opp
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
__has_include: __has_include.o
__user: __user.o
__stringify: __stringify.o
__STDC__: __STDC__.o
_XOPEN_SOURCE: _XOPEN_SOURCE.o
_POSIX_SOURCE: _POSIX_SOURCE.o
_POSIX_C_SOURCE: _POSIX_C_SOURCE.o
LINUX_VERSION_CODE: LINUX_VERSION_CODE.o

CFLAGS___i386__ := -m32
CFLAGS___x86_64__ := -m64
CFLAGS___WORDSIZE-32 := -m32
CFLAGS_machine := -Wno-error=deprecated -Wno-deprecated
CFLAGS___user := -Wno-error=attributes

%-macros.h:
	@echo -e "  ${CC} MARCOS  \033[1m$(CC)-macros.h\033[m"
	${Q}rm -f compiler-macros.h
	@echo '#pragma once' | tee $(@)
	${Q}$(CC) -march=native -E -dM - </dev/null | tee --append $(@)

compiler-macros.h: $(CC)-macros.h
	@echo -e "  CC MARCOS  \033[1mcompiler-macros.h\033[m"
	${Q}rm -f $(@)
	@ln -s $(<) $(@)

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.opp: %.cpp
	@echo -e "  CXX  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CXX) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_CXX): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CXX) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_CXX} *.o *.opp
	${Q}rm -f $(CC)-macros.h compiler-macros.h
