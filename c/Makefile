# SPDX-License-Identifier: GPL-3.0
include ../kconfig.mk
CC := gcc
include ../compiler/compiler.mk

targets :=
targets += arg
targets += argv
targets += auto
targets += approaching
targets += array
targets += ascii
targets += arch-unsigned-signed
targets += alignas
targets += case
targets += const
targets += dummy
targets += param-pass
targets += compat
targets += compare
targets += _Generic
targets += goto
targets += ptr-dim
targets += struct
targets += string
targets += union
targets += xor
targets += __alignof__
targets += __has_include __has_feature
targets += __label__
targets += __typeof__
targets += NULL
targets += _Nullable
targets += _Nonnull
targets += BUILD_BUG_ON_ZERO
targets += macro
targets += while while-sleep
targets += stub
targets += if
targets += enum
targets += __STDC__ __STDC__gnu98 __STDC__c98 __STDC__c17
targets += include_next
targets += unsigned
targets += restrict
targets += ternary
targets += return

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
targets-prep := ${targets:=.E.c}

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
