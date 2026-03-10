# SPDX-License-Identifier: GPL-3.0
include qcow2.mk

target-y := qcow2
QCOW2S := a.qcow2

target-prep-y := ${QCOW2S}
target-test-y := test-qcow2

qcow2-objs := qcow2_helpers.o

include main.mk

%.qcow2:
	$(call log_tgt,QCOW2,$(@))
	$(call create_qcow2,$(@),1G)

test-qcow2: ${QCOW2S}
	$(call log_tgt,TEST,$(@))
	${Q}./qcow2 -q a.qcow2 --verbose
