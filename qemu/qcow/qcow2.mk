# SPDX-License-Identifier: GPL-3.0
QEMU_IMG := qemu-img

define create_qcow2
	${Q}${QEMU_IMG} create -f qcow2 $(1) $(2) && ${QEMU_IMG} info $(1)
endef
