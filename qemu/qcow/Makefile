# SPDX-License-Identifier: GPL-3.0
include qcow2.mk

target-y := qcow2
QCOW2S := a.qcow2

target-prep-y := ${QCOW2S}
target-test-y := test-qcow2

include ../../template/main.mk

qcow2_helpers.o: qcow2_helpers.h qcow2.h
qcow2: qcow2.o qcow2_helpers.o

%.qcow2:
	$(call log_tgt_exe,QCOW2,,$(@))
	$(call create_qcow2,$(@),1G)

test-qcow2: ${QCOW2S}
	$(call log_tgt_exe,TEST,,$(@))
	${Q}./qcow2 -q a.qcow2 --verbose
