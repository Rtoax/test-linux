# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - GIT_TOPDIR=
# - GIT_CONFIG_CORE_HOOKSPATH=
#
ifndef _GIT_MK
export _GIT_MK = 1

# Note: top Makefile use git.mk, before install, we could not include template
# mk in here.
ifndef _DIR_MK
  include dir.mk
endif

GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)

GIT_CONFIG_CORE_HOOKSPATH := $(shell git config get core.hooksPath 2>/dev/null \
	|| git config core.hooksPath 2>/dev/null \
	|| echo "UnsupportGetHooks")


define git_config
	@if [[ ! -z $(TOPDIR) ]]; then \
		${SHELL} ${TOPDIR}/scripts/git/hooks/config.sh; \
	fi
endef

define git_archive
	@if [[ ! -z $(TOPDIR) ]]; then \
		${SHELL} ${TOPDIR}/scripts/git/archive.sh; \
	fi
endef

# $1: Y or N
define git_clean
	@if [[ ! -z $(TOPDIR) ]]; then \
		${SHELL} ${TOPDIR}/scripts/git/clean.sh $(1); \
	fi
endef

endif
