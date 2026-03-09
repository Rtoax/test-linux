# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - CGROUPFS_ROOT=[/sys/fs/cgroup]
# - CGROUP_V1=[y|n]
# - CGROUP_V2=[y|n]
#
ifndef _CGROUP_MK
_CGROUP_MK = 1

CGROUPFS_ROOT := /sys/fs/cgroup

ifeq ($(shell [[ -d "${CGROUPFS_ROOT}/memory" ]] && echo "yes" || echo "no"), yes)
  CGROUP_V1 := y
else
  CGROUP_V1 := n
endif

ifneq ($(wildcard ${CGROUPFS_ROOT}/cgroup.controllers),)
  CGROUP_V2 := y
else
  CGROUP_V2 := n
endif

ifdef DEBUG
  $(info CGROUPFS_ROOT = ${CGROUPFS_ROOT})
  $(info CGROUP_V1 = ${CGROUP_V1})
  $(info CGROUP_V2 = ${CGROUP_V2})
endif

export CGROUPFS_ROOT
export CGROUP_V1
export CGROUP_V2

endif
