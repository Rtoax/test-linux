# SPDX-License-Identifier: GPL-3.0
SHELL = bash

.PHONY: build
build:
	echo $(firstword $(MAKECMDGOALS))

