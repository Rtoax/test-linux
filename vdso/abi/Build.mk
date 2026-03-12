# SPDX-License-Identifier: GPL-3.0
include vdso.mk

target-prep-y := lib${VDSO_NAME}.custom.so
target-prep-y += lib${VDSO_NAME}.copy.so
target-prep-y += ${VDSO_NAME}
target-prep-y += main-custom main-kernel
