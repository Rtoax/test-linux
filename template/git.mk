# SPDX-License-Identifier: GPL-3.0
_GIT = 1

ifeq (${TOPDIR},)
  $(error Not define TOPDIR)
endif

define git_config
	@if [[ ! -z $(TOPDIR) ]]; then \
		${SHELL} ${TOPDIR}/scripts/git/config.sh; \
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
