# SPDX-License-Identifier: GPL-3.0
#
# https://github.com/pmem/ndctl
# -----------------------------
# A "device memory" enabling project encompassing tools and libraries for
# CXL, NVDIMMs, DAX, memory tiering and other platform memory device topics.
#
# https://git.kernel.org/pub/scm/linux/kernel/git/nvdimm/nvdimm.git/
#
# Output definitions:
# - NDCTL=[/usr/bin/ndctl]
# - HAVE_NDCTL=[y|n]
#
ifndef _NDCTL_MK
_NDCTL_MK = 1

include shell.mk
include define.mk

$(call find_cmd_and_def,ndctl)

ifeq (${NDCTL},)
  $(warning Not found ndctl, please install first)
else

endif # end of found NDCTL

endif # end of _NDCTL_MK
