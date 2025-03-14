# SPDX-License-Identifier: GPL-3.0
sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-test := $(addprefix $(shell pwd)/,$(sub-dir:=.test))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

