# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
_KCOMPILE_MK = 1

VMLINUX := /usr/lib/debug/lib/modules/$(shell uname -r)/vmlinux
KDIR := /lib/modules/$(shell uname -r)/build

ifneq ($(wildcard ${VMLINUX}),)
  $(info Build with VMLINUX=${VMLINUX})
  ifeq ($(wildcard ${KDIR}/vmlinux),)
    # TODO: could non copy?
    $(shell sudo cp ${VMLINUX} ${KDIR}/vmlinux)
    $(info Copy ${VMLINUX} to ${KDIR})
  endif
endif

