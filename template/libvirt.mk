# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - VIRSH=[/usr/bin/virsh]
# - HAVE_VIRSH=[y|n]
# - HAVE_LIBVIRT=[y|n]
#
ifndef _LIBVIRT_MK
_LIBVIRT_MK = 1

include define.mk

$(call find_cmd_and_def,virsh)

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
