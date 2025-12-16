# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Output definitions:
# - CONFIG_KERNEL=
# - CONFIG_CURDIR_KCONFIG=
# - AUTOCONFIG_H=
#
_KCONFIG = 1

include dir.mk

CONFIG_KERNEL := /boot/config-$(shell uname -r)
AUTOCONFIG_H := /usr/lib/modules/$(shell uname -r)/include/generated/autoconf.h
CONFIG_CURDIR_KCONFIG := ${CONFIG_KERNEL}

# If don't have kernel config, include default kconfig file.
ifeq ($(wildcard $(CONFIG_KERNEL)),)
  $(warning "WARNING: Not found ${CONFIG_KERNEL}, use ${TOPDIR}/kconfig instead")

  CONFIG_KERNEL := ${TOPDIR}/kconfig

  # If current directory has kconfig, include it.
  CONFIG_CURDIR_KCONFIG := kconfig
  ifneq ($(wildcard ${CONFIG_CURDIR_KCONFIG}),)
    ifdef DEBUG
      $(info "INFO: current directory include ${CONFIG_CURDIR_KCONFIG} file")
    endif
    include ${CONFIG_CURDIR_KCONFIG}
  endif
endif
include $(CONFIG_KERNEL)

export CONFIG_KERNEL CONFIG_CURDIR_KCONFIG

ifdef DEBUG
  $(info CONFIG_KERNEL = ${CONFIG_KERNEL})
  $(info CONFIG_CURDIR_KCONFIG = ${CONFIG_CURDIR_KCONFIG})
endif

define display_all_kconfig
	@configs=($$(find ${TOPDIR} -name kconfig -type f)); \
		cat $${configs[@]} | grep -e '^CONFIG_' -e '^# CONFIG_' | sort -u
endef
