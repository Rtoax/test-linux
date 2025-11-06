# SPDX-License-Identifier: GPL-3.0
#
# Output defintions:
# - GIT_CONFIG_CORE_HOOKSPATH=
#
_GIT = 1

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

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

define git_clean
	@if [[ ! -z $(TOPDIR) ]]; then \
		${SHELL} ${TOPDIR}/scripts/git/clean.sh; \
	fi
endef
