# SPDX-License-Identifier: GPL-3.0
include compiler.mk

target-${CC__Float16} += _Float16
target-${CC__Float128} += _Float128
target-${CC___float80} += __float80
target-${CC___float128} += __float128
target-${CC___bf16} += __bf16

CFLAGS := ${cflags-support-types-y}
CFLAGS += ${cflags-support-headers-y}
CFLAGS += -Wno-error=unused-variable
LDFLAGS += ${ldflags-support-headers-y}
