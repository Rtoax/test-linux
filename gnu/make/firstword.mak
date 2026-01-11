# SPDX-License-Identifier: GPL-3.0
include shell.mk

.PHONY: build
build:
	echo $(firstword $(MAKECMDGOALS))

