# SPDX-License-Identifier: GPL-3.0
target-y := qcow2
QCOW2S := a.qcow2

target-prep-y := ${QCOW2S}
target-post-y := post-qcow2

qcow2-objs := qcow2_helpers.o
