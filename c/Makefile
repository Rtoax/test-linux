# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include ../template/kconfig.mk
CC := gcc
include ../compiler/compiler.mk

target-y :=
target-y += arg
target-y += argv
target-y += auto
target-y += approaching
target-y += array
target-y += ascii
target-y += arch-unsigned-signed
target-y += alignas
target-y += case
target-y += const
target-y += dummy
target-y += param-pass
target-y += compat
target-y += compare
target-y += _Generic
target-y += goto
target-y += float
target-${CC___bf16} += __bf16
target-${CC___float128} += __float128
target-${CC__Float128} += _Float128
target-${CC___float80} += __float80
target-y += ptr-dim
target-y += struct
target-y += string
target-y += union
target-y += xor
target-y += __alignof__
target-y += __has_include __has_feature
target-y += __label__
target-y += __typeof__
target-y += NULL
target-y += _Nullable
target-y += _Nonnull
target-y += BUILD_BUG_ON_ZERO
target-y += macro
target-y += while while-sleep
target-y += stub
target-y += if
target-y += enum
target-y += __STDC__ __STDC__gnu98 __STDC__c98 __STDC__c17
target-y += include_next
target-y += unsigned
target-y += restrict
target-y += ternary
target-y += return
target-y += overflow

define arch_strip
  ${Q}${STRIP} $(1) -o $(1).strip
endef

CFLAGS :=
LDFLAGS :=

include ../compiler/cross-compile.mk

CFLAGS += -I../macro/

CFLAGS_auto := -Wno-error=implicit-int
CFLAGS_param-pass := -O0 -I../macro/
CFLAGS_param-pass += -Wno-error=strict-prototypes
ifeq (${CC_STD_GNU17},y)
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

CFLAGS_float := ${cflags-support-types-y}
CFLAGS___float128 := ${cflags-support-types-y}
CFLAGS__Float128 := ${cflags-support-types-y}
LDFLAGS_float := -lm

# preprocessing
target-prep-y := $(patsubst %,${OUTPUT}%.E.c,$(target-y))

include ../template/main.mk

arg: ${OUTPUT}arg.o
argv: ${OUTPUT}argv.o
auto: ${OUTPUT}auto.o
approaching: ${OUTPUT}approaching.o
ascii: ${OUTPUT}ascii.o
alignas: ${OUTPUT}alignas.o
arch-unsigned-signed: ${OUTPUT}arch-unsigned-signed.o
case: ${OUTPUT}case.o
const: ${OUTPUT}const.o
param-pass: ${OUTPUT}param-pass.o
array: ${OUTPUT}array.o
compat: ${OUTPUT}compat.o
compare: ${OUTPUT}compare.o
dummy: ${OUTPUT}dummy.o
float: ${OUTPUT}float.o
__bf16: ${OUTPUT}__bf16.o
__float128: ${OUTPUT}__float128.o
_Float128: ${OUTPUT}_Float128.o
__float80: ${OUTPUT}__float80.o
_Generic: ${OUTPUT}_Generic.o
goto: ${OUTPUT}goto.o
ptr-dim: ${OUTPUT}ptr-dim.o ${OUTPUT}c_helpers.o
struct: ${OUTPUT}struct.o
string: ${OUTPUT}string.o
union: ${OUTPUT}union.o
xor: ${OUTPUT}xor.o
__alignof__: ${OUTPUT}__alignof__.o
__has_include: ${OUTPUT}__has_include.o
__has_feature: ${OUTPUT}__has_feature.o
__label__: ${OUTPUT}__label__.o
__typeof__: ${OUTPUT}__typeof__.o
NULL: ${OUTPUT}NULL.o
_Nullable: ${OUTPUT}_Nullable.o
_Nonnull: ${OUTPUT}_Nonnull.o
BUILD_BUG_ON_ZERO: ${OUTPUT}BUILD_BUG_ON_ZERO.o
macro: ${OUTPUT}macro.o
while: ${OUTPUT}while.o
while-sleep: ${OUTPUT}while-sleep.o
stub: ${OUTPUT}stub.o
if: ${OUTPUT}if.o
enum: ${OUTPUT}enum.o
__STDC__: ${OUTPUT}__STDC__.o
__STDC__c98: ${OUTPUT}__STDC__c98.o
__STDC__gnu98: ${OUTPUT}__STDC__gnu98.o
__STDC__c17: ${OUTPUT}__STDC__c17.o
include_next: ${OUTPUT}include_next.o
unsigned: ${OUTPUT}unsigned.o
restrict: ${OUTPUT}restrict.o
ternary: ${OUTPUT}ternary.o
return: ${OUTPUT}return.o
overflow: ${OUTPUT}overflow.o
