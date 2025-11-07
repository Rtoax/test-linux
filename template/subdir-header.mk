# SPDX-License-Identifier: GPL-3.0
#
# Input defintions:
# - NOSUBDIR: use for skip all sub-directory
_SUBDIR_HEADER = 1

subdir-y ?=

ABS_CURRENT_DIR := $(shell realpath .)
CURRENT_DIR := ${ABS_CURRENT_DIR}

ifdef NOSUBDIR
  subdir-y :=
endif

subdir-y-build := $(addprefix $(CURRENT_DIR)/,$(subdir-y:=.build))
subdir-y-test := $(addprefix $(CURRENT_DIR)/,$(subdir-y:=.test))
subdir-y-clean := $(addprefix $(CURRENT_DIR)/,$(subdir-y:=.clean))

ifdef DEBUG
  $(info subdir-y = ${subdir-y})
endif
