# SPDX-License-Identifier: GPL-3.0
_SUBDIR_HEADER = 1

sub-dir ?=

ABS_CURRENT_DIR := $(shell realpath .)
CURRENT_DIR := ${ABS_CURRENT_DIR}

sub-dir-build := $(addprefix $(CURRENT_DIR)/,$(sub-dir:=.build))
sub-dir-test := $(addprefix $(CURRENT_DIR)/,$(sub-dir:=.test))
sub-dir-clean := $(addprefix $(CURRENT_DIR)/,$(sub-dir:=.clean))

ifdef DEBUG
  $(info sub-dir = ${sub-dir})
endif
