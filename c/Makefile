# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
include ../kconfig.mk
include ../compiler/compiler.mk

CC := gcc
TARGETS :=
EXTRA_TARGETS :=

TARGETS += arg
TARGETS += auto
TARGETS += array
TARGETS += ascii
TARGETS += arch-unsigned-signed
TARGETS += alignas
TARGETS += case
TARGETS += const
TARGETS += dummy
TARGETS += param-pass
TARGETS += compat
TARGETS += compare
TARGETS += _Generic
TARGETS += goto
TARGETS += ptr-dim
TARGETS += struct
TARGETS += union
TARGETS += xor
TARGETS += __alignof__
TARGETS += __has_include __has_feature
TARGETS += __label__
TARGETS += __typeof__
TARGETS += NULL
TARGETS += _Nullable
TARGETS += _Nonnull
TARGETS += BUILD_BUG_ON_ZERO
TARGETS += macro
TARGETS += while while-sleep
TARGETS += stub
TARGETS += if
TARGETS += enum
TARGETS += __STDC__
TARGETS += include_next
TARGETS += unsigned
TARGETS += restrict
TARGETS += ternary
TARGETS += return

define arch_strip
  ${Q}${STRIP} $(1) -o $(1).strip
endef

CFLAGS :=
LDFLAGS :=

include ../compiler/cross-compile.mk

CFLAGS += -Werror -Wall
CFLAGS += -I../macro/

ifeq ($(shell uname -m),sw_64)
  ifeq ($(shell lscpu | grep -o WX-H8000 || true),WX-H8000)
    CFLAGS += -mcpu=sw8a
  else ifeq ($(shell lscpu | grep -o SW3231 || true),SW3231)
    CFLAGS += -mcpu=sw6b
  endif
endif

ifdef STATIC
  LDFLAGS += -static
  $(info Defined STATIC)
endif

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
  ifneq (${CC_M32},1)
    $(error ${CC} not support -m32)
  endif
endif

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g -ggdb
endif

include ../elf/pie.mk

CFLAGS_param-pass := -O0
CFLAGS_auto := -Wno-error=implicit-int
CFLAGS_param-pass := -O0 -I../macro/
ifeq (${CC_STD_GNU17},1)
  CFLAGS_alignas := -std=gnu17
endif
CFLAGS_if := -Wno-error=unused-value -Wno-unused-value
CFLAGS__Generic := -Wno-all
CFLAGS_case := -Wno-error=unused-label -Wno-unused-label
CFLAGS_include_next := -Dinclude/ -Wno-error
CFLAGS_while-sleep := -DWHILE_SLEEP=1
CFLAGS_macro := -DCONFIG_MMU=$(CONFIG_MMU)
CFLAGS_struct := -Wno-gnu-designator -Wno-initializer-overrides

ifdef RETURN_VALUE
  CFLAGS_return := -DRETURN_VALUE=${RETURN_VALUE}
endif

CLANG_TARGET := clang.already.test.out

ifneq (${CC},clang)
  EXTRA_TARGETS += ${CLANG_TARGET}
endif

.PHONY: build
build: ${TARGETS} ${EXTRA_TARGETS}
	@echo -e " \033[1;33m Done \033[m"

${CLANG_TARGET}:
	${Q}./clang.sh
	${Q}touch ${CLANG_TARGET}

arg: arg.o
auto: auto.o
ascii: ascii.o
alignas: alignas.o
arch-unsigned-signed: arch-unsigned-signed.o
case: case.o
const: const.o
param-pass: param-pass.o
array: array.o
compat: compat.o
compare: compare.o
dummy: dummy.o
_Generic: _Generic.o
goto: goto.o
ptr-dim: ptr-dim.o c_helpers.o
struct: struct.o
union: union.o
xor: xor.o
__alignof__: __alignof__.o
__has_include: __has_include.o
__has_feature: __has_feature.o
__label__: __label__.o
__typeof__: __typeof__.o
NULL: NULL.o
_Nullable: _Nullable.o
_Nonnull: _Nonnull.o
BUILD_BUG_ON_ZERO: BUILD_BUG_ON_ZERO.o
macro: macro.o
while: while.o
while-sleep: while-sleep.o
stub: stub.o
if: if.o
enum: enum.o
__STDC__: __STDC__.o
include_next: include_next.o
unsigned: unsigned.o
restrict: restrict.o
ternary: ternary.o
return: return.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -o $(@:.o=.pic.o) -c $(<) -fpic $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.pic.s) -fpic $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -E $(<) -o $(<:.c=.E.c) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(call arch_strip,$(@))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) ${EXTRA_TARGETS}\033[m"
	${Q}rm -f ${TARGETS} ${EXTRA_TARGETS} *.o *.d *.s *.E.c *.strip
