# SPDX-License-Identifier: GPL-3.0
include compiler.mk

target-y += double
target-y += float
target-${CC_SUPPORT_TYPE__Float16} += _Float16
target-${CC_SUPPORT_TYPE__Float32} += _Float32
target-${CC_SUPPORT_TYPE__Float64} += _Float64
target-${CC_SUPPORT_TYPE__Float128} += _Float128
target-${CC_SUPPORT_TYPE__float80} += __float80
target-${CC_SUPPORT_TYPE___float128} += __float128
target-${CC_SUPPORT_TYPE___bf16} += __bf16

CFLAGS := ${cflags-support-types-y}
CFLAGS += ${cflags-support-headers-y}
CFLAGS += -Wno-error=unused-variable

LDFLAGS += ${ldflags-support-headers-y}
