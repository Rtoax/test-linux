# SPDX-License-Identifier: GPL-3.0
target-y += close
ifneq ($(wildcard /usr/include/linux/close_range.h),)
  target-y += close_range
else
  $(warning "WARNING: not found /usr/include/linux/close_range.h")
endif
