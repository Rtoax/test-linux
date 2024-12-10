# SPDX-License-Identifier: GPL-3.0
SHELL = bash

ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

CPU_VENDOR_ID=$(shell lscpu | grep ^Vendor | awk '{print $$3}')

GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)

LIBS_TOPDIR := $(GIT_TOPDIR)/libs/
NUMA_TOPDIR := $(GIT_TOPDIR)/numa/

CFLAGS += -I${LIBS_TOPDIR}
CFLAGS += -I${NUMA_TOPDIR}

libtest-linux-c.a:
	@echo -e "  GEN  \033[1;32m$(@)\033[m"
	${Q}make -C ${LIBS_TOPDIR} $(@)
	${Q}cp ${LIBS_TOPDIR}/libtest-linux-c.a $(shell pwd)

libtest-linux-numa.a:
	@echo -e "  GEN  \033[1;32m$(@)\033[m"
	${Q}make -C ${NUMA_TOPDIR} $(@)
	${Q}cp ${NUMA_TOPDIR}/libtest-linux-numa.a $(shell pwd)


# Store some common function

define git_config
	@if [[ ! -z $(GIT_TOPDIR) ]]; then \
		${SHELL} ${GIT_TOPDIR}/scripts/git/config.sh; \
	fi
endef

define git_archive
	@if [[ ! -z $(GIT_TOPDIR) ]]; then \
		${SHELL} ${GIT_TOPDIR}/scripts/git-archive; \
	fi
endef

define git_clean
	@if [[ ! -z $(GIT_TOPDIR) ]]; then \
		${SHELL} ${GIT_TOPDIR}/scripts/git-clean; \
	fi
endef

