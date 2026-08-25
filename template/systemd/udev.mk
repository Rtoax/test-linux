# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_SYSTEMD_LIBUDEV_H=[y|n]
#
ifndef _SYSTEMD_UDEV_MK
_SYSTEMD_UDEV_MK = 1

include define.mk

$(call check_file_and_def,/usr/include/libudev.h,HAVE_SYSTEMD_LIBUDEV_H)

endif # end of _SYSTEMD_UDEV_MK
