# SPDX-License-Identifier: GPL-3.0
include qcow2.mk

TARGETS := qcow2
QCOW2S := a.qcow2

TARGETS_PREP := ${QCOW2S}
TARGETS_TEST := test-qcow2

include ../../template/main.mk

qcow2_helpers.o: qcow2_helpers.h qcow2.h
qcow2: qcow2.o qcow2_helpers.o

%.qcow2:
	@echo -e "  QCOW2 \033[1m$(@)\033[m"
	$(call create_qcow2,$(@),1G)

test-qcow2: ${QCOW2S}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	${Q}./qcow2 -q a.qcow2 --verbose
