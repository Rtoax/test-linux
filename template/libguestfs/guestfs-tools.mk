# SPDX-License-Identifier: GPL-3.0
#
# https://github.com/libguestfs/guestfs-tools
#
# Output definitions:
# - VIRT_DF=[/usr/bin/virt-df]
# - HAVE_VIRT_DF=[y|n]
#
ifndef _LIBGUESTFS_GUESTFS_TOOLS_MK
_LIBGUESTFS_GUESTFS_TOOLS_MK = 1

include define.mk

$(call find_cmd_and_def,virt-df)

endif # end of _LIBGUESTFS_GUESTFS_TOOLS_MK
