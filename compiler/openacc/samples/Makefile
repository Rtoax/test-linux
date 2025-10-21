# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-y := hello
target-y += acc_get_num_devices

CFLAGS := -fopenacc
LDFLAGS := -fopenacc

include ../../../template/main.mk

hello: ${OUTPUT}hello.o
acc_get_num_devices: ${OUTPUT}acc_get_num_devices.o
