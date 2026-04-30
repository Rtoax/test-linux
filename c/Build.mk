# SPDX-License-Identifier: GPL-3.0
include kconfig.mk
include compiler.mk

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
target-y += _Static_assert
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
target-y += __STDC__
target-y += __STDC__gnu98
target-y += __STDC__c98
target-${CC_STD_C11} += __STDC__c11
target-${CC_STD_C17} += __STDC__c17
target-y += include_next
target-y += unsigned
target-y += restrict
target-y += ternary
target-y += return
target-y += overflow
target-y += typeof

# preprocessing
target-prep-y := $(patsubst %,${OUTPUT}%.E.c,$(target-y))
target-prep-y += ${OUTPUT}return.o.bin

ptr-dim-objs := c_helpers.o
__STDC__gnu98-objs := __STDC__.1.o
__STDC__c98-objs := __STDC__.2.o
__STDC__c11-objs := __STDC__.3.o
__STDC__c17-objs := __STDC__.4.o

define arch_strip
  ${Q}${STRIP} $(1) -o $(1).strip
endef

include cross-compile.mk

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
CFLAGS___STDC__.1 := -std=gnu89 -DSTD_GNU98=1
CFLAGS___STDC__.2 := -std=c89 -DSTD_C98=1
CFLAGS___STDC__.3 := -std=c11 -DSTD_C11=1
CFLAGS___STDC__.4 := -std=c17 -DSTD_C17=1

CFLAGS_float := ${cflags-support-types-y}
CFLAGS___float128 := ${cflags-support-types-y}
CFLAGS___float128 += ${cflags-support-headers-y}
CFLAGS___float128 += -Wno-error=unused-variable
LDFLAGS___float128 += ${ldflags-support-headers-y}
CFLAGS__Float128 := ${cflags-support-types-y}
CFLAGS__Float128 += ${cflags-support-headers-y}
CFLAGS__Float128 += -Wno-error=unused-variable
LDFLAGS__Float128 += ${ldflags-support-headers-y}
LDFLAGS_float := -lm
