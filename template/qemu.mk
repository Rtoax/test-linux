# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - HAVE_QEMU_NBD=[y|n]
#
ifndef _QEMU_MK
_QEMU_MK = 1

QEMU_NBD := $(shell which qemu-nbd 2>/dev/null)
ifneq (${QEMU_NBD},)
  HAVE_QEMU_NBD := y
else
  HAVE_QEMU_NBD := n
endif

ifdef DEBUG
  $(info QEMU_NBD = ${QEMU_NBD})
  $(info HAVE_QEMU_NBD = ${HAVE_QEMU_NBD})
endif

export QEMU_NBD
export HAVE_QEMU_NBD

endif
