# SPDX-License-Identifier: GPL-3.0
SHELL ?= bash

CONFIG_TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
CONFIG_KERNEL ?= /boot/config-$(shell uname -r)

# If don't have kernel config, include default kconfig file.
ifeq ($(wildcard $(CONFIG_KERNEL)),)
  $(warning "WARNING: Not found ${CONFIG_KERNEL}, use ${CONFIG_TOPDIR}/kconfig")
  CONFIG_KERNEL := ${CONFIG_TOPDIR}/kconfig
endif
include $(CONFIG_KERNEL)

# If current directory has kconfig, include it.
CONFIG_CURDIR_KCONFIG ?= kconfig
ifneq ($(wildcard ${CONFIG_CURDIR_KCONFIG}),)
  $(info "INFO: current directory include ${CONFIG_CURDIR_KCONFIG} file")
  include ${CONFIG_CURDIR_KCONFIG}
endif

export CONFIG_KERNEL CONFIG_CURDIR_KCONFIG

define display_all_kconfig
	@configs=($$(find ${CONFIG_TOPDIR} -name kconfig)); \
		cat $${configs[@]} | grep -e '^CONFIG_' -e '^# CONFIG_' | sort | uniq
endef
