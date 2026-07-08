# SPDX-License-Identifier: GPL-3.0
include kconfig.mk
include compiler.mk

SRC_SFX_LIST := $(shell seq 1 1 20)

target-y += arg
target-y += argv
target-y += auto
target-y += approaching
target-y += array
target-y += ascii
target-y += assignment
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
target-y += __STDC__c89 __STDC__gnu89
target-y += __STDC__c90 __STDC__gnu90
target-y += __STDC__c99 __STDC__gnu99
target-${CC_SUPPORT_STD_C11} += __STDC__c11 __STDC__gnu11
target-${CC_SUPPORT_STD_C17} += __STDC__c17 __STDC__gnu17
target-${CC_SUPPORT_STD_C23} += __STDC__c23 __STDC__gnu23
target-y += include_next
target-y += unsigned
target-y += restrict
target-y += ternary
target-y += return
target-y += overflow
target-y += typeof

# preprocessing
prep-y := ${OUTPUT}return.o.bin

ptr-dim-objs := c_helpers.o
__STDC__c89-objs := __STDC__.1.o
__STDC__c90-objs := __STDC__.2.o
__STDC__c99-objs := __STDC__.3.o
__STDC__c11-objs := __STDC__.4.o
__STDC__c17-objs := __STDC__.5.o
__STDC__c23-objs := __STDC__.6.o

__STDC__gnu89-objs := __STDC__.10.o
__STDC__gnu90-objs := __STDC__.11.o
__STDC__gnu99-objs := __STDC__.12.o
__STDC__gnu11-objs := __STDC__.13.o
__STDC__gnu17-objs := __STDC__.14.o
__STDC__gnu23-objs := __STDC__.15.o

define arch_strip
  ${Q}${STRIP} $(1) -o $(1).strip
endef

include cross-compile.mk

CFLAGS += -I../macro/

CFLAGS_assignment := -Wno-error=uninitialized
CFLAGS_auto := -Wno-error=implicit-int
CFLAGS_param-pass := -O0 -I../macro/
CFLAGS_param-pass += -Wno-error=strict-prototypes
ifeq (${CC_SUPPORT_STD_GNU17},y)
  CFLAGS_alignas := -std=gnu17
endif
CFLAGS_if := -Wno-error=unused-value -Wno-unused-value
CFLAGS__Generic := -Wno-all
CFLAGS_case := -Wno-error=unused-label -Wno-unused-label
CFLAGS_include_next := -Dinclude/ -Wno-error
CFLAGS_while-sleep := -DWHILE_SLEEP=1
CFLAGS_macro := -DCONFIG_MMU=$(CONFIG_MMU)
CFLAGS_struct := -Wno-gnu-designator -Wno-initializer-overrides
CFLAGS___STDC__.1 := -std=c89 -DSTD_C89=1
CFLAGS___STDC__.2 := -std=c90 -DSTD_C90=1
CFLAGS___STDC__.3 := -std=c99 -DSTD_C99=1
CFLAGS___STDC__.4 := -std=c11 -DSTD_C11=1
CFLAGS___STDC__.5 := -std=c17 -DSTD_C17=1
CFLAGS___STDC__.6 := -std=c23 -DSTD_C23=1

CFLAGS___STDC__.10 := -std=gnu89 -DSTD_GNU89=1
CFLAGS___STDC__.11 := -std=gnu90 -DSTD_GNU90=1
CFLAGS___STDC__.12 := -std=gnu99 -DSTD_GNU99=1
CFLAGS___STDC__.13 := -std=gnu11 -DSTD_GNU11=1
CFLAGS___STDC__.14 := -std=gnu17 -DSTD_GNU17=1
CFLAGS___STDC__.15 := -std=gnu23 -DSTD_GNU23=1

CFLAGS_float := ${cflags-support-types-y}
LDFLAGS_float := -lm
