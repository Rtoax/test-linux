# SPDX-License-Identifier: GPL-3.0
target-y := hello
target-y += acc_get_num_devices

CFLAGS := -fopenacc
LDFLAGS := -fopenacc
