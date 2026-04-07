# SPDX-License-Identifier: GPL-3.0
include helpers.mk

target-y := qcow2
QCOW2S := a.qcow2

target-prep-y := ${QCOW2S}
target-post-y := post-qcow2

qcow2-objs := ${QCOW2_HELPERS}
