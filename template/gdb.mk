# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Output definitions:
# - GDB=[/usr/bin/gdb]
# - HAVE_GDB=[y|n]
#
# Functions:
# - gdb_{gt,ge,eq,lt,le}(major, minor)=[y|n]
#
ifndef _GDB_MK
_GDB_MK = 1

include define.mk
include version.mk

$(call find_cmd_and_def,gdb)

gdbversh = ${TOPDIR}/scripts/version/version.sh -n gdb

GDB_VERSION := $(shell ${gdbversh} --version)
GDB_MAJOR := $(shell ${gdbversh} -- --major)
GDB_MINOR := $(shell ${gdbversh} -- --minor)

$(eval $(call define_version,gdb,version2_code100010,y,${GDB_MAJOR},${GDB_MINOR}))

# Note: update newest version here.
__gdb_newest_check = $(call gdb_le,17,2)
ifneq ($(__gdb_newest_check), y)
  $(error call gdb_le failed, ${__gdb_newest_check})
endif
# Centos8 gdb is 8.2
ifneq ($(call gdb_gt,8,0), y)
  $(error call gdb_gt 8.0 failed)
endif

endif
