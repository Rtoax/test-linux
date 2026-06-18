# SPDX-License-Identifier: GPL-3.0
include vdso.mk

prep-y := lib${VDSO_NAME}.custom.so
prep-y += lib${VDSO_NAME}.copy.so
prep-y += ${VDSO_NAME}
prep-y += main-custom main-kernel
