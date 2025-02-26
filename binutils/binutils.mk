# SPDX-License-Identifier: GPL-3.0
SHELL = bash

LD_BFD := $(shell which ld.bfd 2>/dev/null)
ifeq ($(LD_BFD),)
  $(error "Not found linker ld.bfd, install binutils first")
else
  $(info LD_BFD = ${LD_BFD})
endif

# Get binutils version
BINUTILS_VERSION := $(shell ${LD_BFD} --version | grep -o [0-9].[0-9]\. | sed -n '1p')
BINUTILS_VERSION_MAJOR := $(shell echo ${BINUTILS_VERSION} | awk -F '.' '{print $$1}')
BINUTILS_VERSION_MINOR := $(shell echo ${BINUTILS_VERSION} | awk -F '.' '{print $$2}')

$(info Binutils version ${BINUTILS_VERSION_MAJOR}.${BINUTILS_VERSION_MINOR})
ifneq (${BINUTILS_VERSION_MAJOR},2)
  $(error Not support binutils ${BINUTILS_VERSION})
endif

