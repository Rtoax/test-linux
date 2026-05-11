# SPDX-License-Identifier: GPL-3.0
include shell.mk

VENDOR_ID := $(shell lscpu | grep ^Vendor | awk '{print $$3}')

define c_name
$(shell str=${1}; echo $${str//[!0-9a-zA-Z]/_})
endef

$(info $(call c_name,mkfs.ext4))

.PHONY: build
build:
	echo $(VENDOR_ID)

