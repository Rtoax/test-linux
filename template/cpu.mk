# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao

CPU_VENDOR_ID := $(shell lscpu | grep ^Vendor | awk '{print $$3}')
