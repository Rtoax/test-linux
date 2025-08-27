# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
_KCOMPILE = 1

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

