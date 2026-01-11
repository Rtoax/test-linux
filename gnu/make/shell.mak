# SPDX-License-Identifier: GPL-3.0
include shell.mk

VENDOR_ID := $(shell lscpu | grep ^Vendor | awk '{print $$3}')

.PHONY: build
build:
	echo $(VENDOR_ID)

