# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - OS_ID=[centos|fedora|ubuntu|debian|cclinux|kylin|...]
# - __centos__=1
# - __debian__=1
# - __fedora__=1
# - __cclinux__=1
# - __kylin__=1
# - __ubuntu__=1
#
# - OS_VERSION_ID=[43|24.04]
# - __os_major__=[43|24]
# - __os_minor__=[0|04]
#
# - OS_CFLAGS+=-DOS_ID=${OS_ID}
#   OS_CFLAGS+=-DOS_VERSION_ID=${OS_VERSION_ID}
#   OS_CFLAGS+=-D__${OS_ID}__=1
#   OS_CFLAGS+=-D__os_major__=[43|24]
#   OS_CFLAGS+=-D__os_minor__=[|04]
#      C source code should use OS_ID like:
#      #ifdef __fedora__
#      #pragma message fedora
#      #endif
#
# Functions:
# - is_os(fedora[ debian ...])=[y|n]
#
ifndef _OS_MK
_OS_MK = 1

include shell.mk

OS_CFLAGS :=

get_distr_info = $(patsubst "%",%,$(shell grep $(1) /etc/os-release 2>/dev/null | \
					awk -F'=' '{print $$2}'))

OS_ID := $(call get_distr_info, '^ID=')
ifeq ($(OS_ID),)
  $(error Not found ID in /etc/os-release)
endif

OS_VERSION_ID := $(call get_distr_info, '^VERSION_ID=')
ifeq ($(OS_VERSION_ID),)
  $(error Not found VERSION_ID in /etc/os-release)
endif

DEBIAN_VERSION_FULL := $(call get_distr_info, '^DEBIAN_VERSION_FULL=')

__os_major__ := $(shell echo ${OS_VERSION_ID} | awk -F '.' '{print $$1}')
__os_minor__ := $(shell echo ${OS_VERSION_ID} | awk -F '.' '{print $$2}')
ifeq (${__os_minor__},)
  ifneq (${DEBIAN_VERSION_FULL},)
    __os_minor__ := $(shell echo ${DEBIAN_VERSION_FULL} | awk -F '.' '{print $$2}')
  endif
endif
ifeq (${__os_minor__},)
  __os_minor__ := 0
endif

# $1: distribution name, like fedora
define define_os
  $(eval OS_CFLAGS += -D__${1}__=1)
  $(eval OS_CFLAGS += -DOS_ID=${1})
  $(eval export __${1}__ = 1)
endef

# $1: distribution name list, like fedora debian
define is_os
$(shell for os in ${1}; do \
          if test $${os} == ${OS_ID}; then \
            echo y; exit 0; \
          fi; \
        done; \
        echo n)
endef

$(call define_os,${OS_ID})

OS_CFLAGS += -DOS_VERSION_ID=${OS_VERSION_ID}
OS_CFLAGS += -D__os_major__=${__os_major__}
OS_CFLAGS += -D__os_minor__=${__os_minor__}

ifdef DEBUG
  $(info OS_ID = ${OS_ID})
  $(info OS_VERSION_ID = ${OS_VERSION_ID})
  $(info __os_major__ = ${__os_major__})
  $(info __os_minor__ = ${__os_minor__})
  $(info OS_CFLAGS = ${OS_CFLAGS})
  $(info is_os ${OS_ID} = $(call is_os,x ${OS_ID} y))
  $(info is_os fedora = $(call is_os,x fedora y))
  $(info is_os debian = $(call is_os,x debian y))
endif

ifneq ($(call is_os,x ${OS_ID} y),y)
  $(error is_os call failed for ${OS_ID})
endif

export OS_ID
export OS_VERSION_ID
export __os_major__
export __os_minor__
export OS_CFLAGS

endif
