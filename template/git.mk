# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Defintions:
# - GIT=[/usr/bin/git]
# - HAVE_GIT=[y|n]
#
# Functions:
# - git_{gt,ge,eq,lt,le}(major, minor, patchlevel)=[y|n]
#
ifndef _GIT_MK
_GIT_MK = 1

include define.mk
include version.mk

$(call find_cmd_and_def,git)

gitversh = ${TOPDIR}/scripts/version/version.sh -n git

GIT_VERSION := $(shell ${gitversh} --version)
GIT_MAJOR := $(shell ${gitversh} -- --major)
GIT_MINOR := $(shell ${gitversh} -- --minor)
GIT_PATCHLEVEL := $(shell ${gitversh} -- --patchlevel)

$(eval $(call define_version,git,version3_code1688,y,${GIT_MAJOR},${GIT_MINOR},${GIT_PATCHLEVEL}))

ifdef DEBUG
  $(info GIT_VERSION = ${GIT_VERSION})
  $(info GIT_MAJOR = ${GIT_MAJOR})
  $(info GIT_MINOR = ${GIT_MINOR})
  $(info GIT_PATCHLEVEL = ${GIT_PATCHLEVEL})
endif

# Note: update newest version here.
__git_newest_check = $(call git_le,2,55,0)
ifneq ($(__git_newest_check), y)
  $(error call git_le failed, ${__git_newest_check})
endif
ifneq ($(call git_gt,0,0,0), y)
  $(error call git_gt failed)
endif

endif
