# SPDX-License-Identifier: GPL-3.0
#
# Input defintions:
# - NOSUBDIR: use for skip all sub-directory
#
ifndef _TARGET_SUBDIR_HEADER_MK
_TARGET_SUBDIR_HEADER_MK = 1

subdir-y ?=

ABS_CURRENT_DIR := $(shell realpath .)
CURRENT_DIR := ${ABS_CURRENT_DIR}

ifdef NOSUBDIR
  subdir-y :=
endif

subdir-y-build := $(addprefix $(CURRENT_DIR)/,$(subdir-y:=.build))
subdir-y-clean := $(addprefix $(CURRENT_DIR)/,$(subdir-y:=.clean))

ifdef DEBUG
  $(info CURRENT_DIR = ${CURRENT_DIR})
  $(info subdir-y = ${subdir-y})
  $(info subdir-y-build = ${subdir-y-build})
  $(info subdir-y-clean = ${subdir-y-clean})
endif

endif
