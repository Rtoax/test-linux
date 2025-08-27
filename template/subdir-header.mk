# SPDX-License-Identifier: GPL-3.0
_SUBDIR_HEADER = 1

sub-dir ?=
kmod-list ?=

ABS_CURRENT_DIR := $(shell realpath .)
CURRENT_DIR := ${ABS_CURRENT_DIR}

kmod-list-build := $(addprefix $(CURRENT_DIR)/,$(kmod-list:=.build))
kmod-list-test := $(addprefix $(CURRENT_DIR)/,$(kmod-list:=.test))
kmod-list-clean := $(addprefix $(CURRENT_DIR)/,$(kmod-list:=.clean))

sub-dir-build := $(addprefix $(CURRENT_DIR)/,$(sub-dir:=.build))
sub-dir-test := $(addprefix $(CURRENT_DIR)/,$(sub-dir:=.test))
sub-dir-clean := $(addprefix $(CURRENT_DIR)/,$(sub-dir:=.clean))

ifdef DEBUG
  $(info sub-dir = ${sub-dir})
  $(info kmod-list = ${kmod-list})
endif
