# SPDX-License-Identifier: GPL-3.0
#
# https://github.com/libguestfs/virt-v2v
#
# Output definitions:
# - VIRT_V2V=[/usr/bin/virt-v2v]
# - HAVE_VIRT_V2V=[y|n]
#
ifndef _LIBGUESTFS_VIRT_V2V_MK
_LIBGUESTFS_VIRT_V2V_MK = 1

include define.mk

$(call find_cmd_and_def,virt-v2v)

endif # end of _LIBGUESTFS_VIRT_V2V_MK
