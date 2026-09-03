# SPDX-License-Identifier: GPL-3.0
#
# https://github.com/libguestfs/libguestfs
#
# Output definitions:
# - GUESTFISH=[/usr/bin/guestfish]
# - GUESTMOUNT=[/usr/bin/guestmount]
# - GUESTUNMOUNT=[/usr/bin/guestunmount]
# - HAVE_GUESTFISH=[y|n]
# - HAVE_GUESTMOUNT=[y|n]
# - HAVE_GUESTUNMOUNT=[y|n]
#
ifndef _LIBGUESTFS_LIBGUESTFS_MK
_LIBGUESTFS_LIBGUESTFS_MK = 1

include define.mk

$(call find_cmd_and_def,guestfish)
$(call find_cmd_and_def,guestmount)
$(call find_cmd_and_def,guestunmount)

endif # end of _LIBGUESTFS_LIBGUESTFS_MK
