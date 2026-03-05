# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - OS_ID=[fedora|ubuntu|debian]
# - __fedora__=1
# - __ubuntu__=1
# - __debian__=1
#
# - OS_VERSION_ID=[43|24.04]
# - __os_major__=[43|24]
# - __os_minor__=[0|04]
#
# - OS_CFLAGS+=-DOS_ID=[fedora|ubuntu|debian]
#   OS_CFLAGS+=-D__fedora__=1
#   OS_CFLAGS+=-D__ubuntu__=1
#   OS_CFLAGS+=-D__debian__=1
#   OS_CFLAGS+=-DOS_VERSION_ID=[43|24.03]
#   OS_CFLAGS+=-D__os_major__=[43|24]
#   OS_CFLAGS+=-D__os_minor__=[|04]
#      C source code should use OS_ID like:
#      #ifdef __fedora__
#      #pragma message fedora
#      #endif
#
ifndef _OS_MK
_OS_MK = 1

OS_CFLAGS :=

get_distr_info = $(patsubst "%",%,$(shell grep $(1) /etc/os-release 2>/dev/null | \
					awk -F'=' '{print $$2}'))

OS_ID := $(call get_distr_info, '^ID=')
OS_VERSION_ID := $(call get_distr_info, '^VERSION_ID=')
__os_major__ := $(shell echo ${OS_VERSION_ID} | awk -F '.' '{print $$1}')
__os_minor__ := $(shell echo ${OS_VERSION_ID} | awk -F '.' '{print $$2}')
ifeq (${__os_minor__},)
  __os_minor__ := 0
endif

ifeq ($(OS_VERSION_ID),)
  $(error Not found VERSION_ID in /etc/os-release)
endif

OS_CFLAGS += -DOS_ID=${OS_ID}
ifeq (${OS_ID},fedora)
  OS_CFLAGS := -D__fedora__=1
  export __fedora__ = 1
else ifeq (${OS_ID},ubuntu)
  OS_CFLAGS := -D__ubuntu__=1
  export __ubuntu__ = 1
else ifeq (${OS_ID},debian)
  OS_CFLAGS := -D__debian__=1
  export __debian__ = 1
else
  $(error "Not support ${OS_ID}, please add it to template/os.mk")
endif

OS_CFLAGS += -DOS_VERSION_ID=${OS_VERSION_ID}
OS_CFLAGS += -D__os_major__=${__os_major__}
OS_CFLAGS += -D__os_minor__=${__os_minor__}

ifdef DEBUG
  $(info OS_ID = ${OS_ID})
  $(info OS_VERSION_ID = ${OS_VERSION_ID})
  $(info __os_major__ = ${__os_major__})
  $(info __os_minor__ = ${__os_minor__})
  $(info OS_CFLAGS = ${OS_CFLAGS})
endif

export OS_ID
export OS_VERSION_ID
export __os_major__
export __os_minor__
export OS_CFLAGS

endif
