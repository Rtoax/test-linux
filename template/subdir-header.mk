# SPDX-License-Identifier: GPL-3.0
sub-dir ?=

sub-dir-build := $(addprefix $(shell realpath .)/,$(sub-dir:=.build))
sub-dir-test := $(addprefix $(shell realpath .)/,$(sub-dir:=.test))
sub-dir-clean := $(addprefix $(shell realpath .)/,$(sub-dir:=.clean))
