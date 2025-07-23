# SPDX-License-Identifier: GPL-3.0
include ../kconfig.mk
CC := gcc
include ../compiler/compiler.mk

TARGETS :=
TARGETS += arg
TARGETS += argv
TARGETS += auto
TARGETS += approaching
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
TARGETS += string
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
TARGETS += __STDC__ __STDC__gnu98 __STDC__c98 __STDC__c17
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

CFLAGS += -I../macro/

ifeq ($(shell uname -m),sw_64)
  ifeq ($(shell lscpu | grep -o WX-H8000 || true),WX-H8000)
    CFLAGS += -mcpu=sw8a
  else ifeq ($(shell lscpu | grep -o SW3231 || true),SW3231)
    CFLAGS += -mcpu=sw6b
  endif
endif

CFLAGS_auto := -Wno-error=implicit-int
CFLAGS_param-pass := -O0 -I../macro/
CFLAGS_param-pass += -Wno-error=strict-prototypes
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
CFLAGS___STDC__c98 := -std=c89 -DSTD_C98=1
CFLAGS___STDC__gnu98 := -std=gnu89 -DSTD_GNU98=1
CFLAGS___STDC__c17 := -std=c89 -DSTD_C17=1

# preprocessing
TARGETS_PREP := ${TARGETS:=.E.c}

include ../template/main.mk

arg: arg.o
argv: argv.o
auto: auto.o
approaching: approaching.o
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
string: string.o
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
__STDC__c98: __STDC__c98.o
__STDC__gnu98: __STDC__gnu98.o
__STDC__c17: __STDC__c17.o
include_next: include_next.o
unsigned: unsigned.o
restrict: restrict.o
ternary: ternary.o
return: return.o
