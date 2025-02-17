# SPDX-License-Identifier: GPL-3.0

KERNEL_VERSION_RAW=$(shell uname -r | grep -o '[0-9]\.[0-9]*\.[0-9]*')
KERNEL_VERSION = $(shell echo ${KERNEL_VERSION_RAW} | awk -F '.' '{print $$1}')
KERNEL_PATCHLEVEL = $(shell echo ${KERNEL_VERSION_RAW} | awk -F '.' '{print $$2}')
KERNEL_SUBLEVEL = $(shell echo ${KERNEL_VERSION_RAW} | awk -F '.' '{print $$3}')

ifdef DEBUG
  $(info KERNEL_VERSION = ${KERNEL_VERSION}.${KERNEL_PATCHLEVEL}.${KERNEL_SUBLEVEL})
endif
