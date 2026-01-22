# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - CGROUPFS_ROOT=[/sys/fs/cgroup]
# - CGROUP_V2=[y|n]
#
ifndef _CGROUP_MK
_CGROUP_MK = 1

CGROUPFS_ROOT := /sys/fs/cgroup

ifneq ($(wildcard ${CGROUPFS_ROOT}/cgroup.controllers),)
  CGROUP_V2 := y
else
  CGROUP_V2 := n
endif

ifdef DEBUG
  $(info CGROUPFS_ROOT = ${CGROUPFS_ROOT})
  $(info CGROUP_V2 = ${CGROUP_V2})
endif

export CGROUPFS_ROOT
export CGROUP_V2

endif
