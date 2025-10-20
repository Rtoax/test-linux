# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include ../template/kconfig.mk
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
targets += float
ifneq (${CC___bf16},)
  targets += __bf16
endif
targets += __float128
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
targets += overflow

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

CFLAGS_float := ${cflags-support-types}
LDFLAGS_float := -lm

# preprocessing
targets-prep := $(patsubst %,${OUTPUT}%.E.c,$(targets))

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
