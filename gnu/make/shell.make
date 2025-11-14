# SPDX-License-Identifier: GPL-3.0
SHELL = bash

VENDOR_ID=$(shell lscpu | grep ^Vendor | awk '{print $$3}')

.PHONY: build
build:
	echo $(VENDOR_ID)

