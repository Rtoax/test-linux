# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBVIRT=[y|n]
#
ifndef _LIBVIRT_MK
_LIBVIRT_MK = 1

VIRSH := $(shell which virsh 2>/dev/null)
ifeq ($(VIRSH),)
  $(warning "Not found libvirt, skipping")
  export HAVE_LIBVIRT := n
else
  export HAVE_LIBVIRT := y
endif # end of libvirt is found

ifdef DEBUG
  $(info HAVE_LIBVIRT = ${HAVE_LIBVIRT})
endif

endif # end of _LIBVIRT_MK
