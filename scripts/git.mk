# SPDX-License-Identifier: GPL-3.0

define git_config
	@if [[ ! -z $(TL_TOPDIR) ]]; then \
		${SHELL} ${TL_TOPDIR}/scripts/git/config.sh; \
	fi
endef

define git_archive
	@if [[ ! -z $(TL_TOPDIR) ]]; then \
		${SHELL} ${TL_TOPDIR}/scripts/git/archive.sh; \
	fi
endef

define git_clean
	@if [[ ! -z $(TL_TOPDIR) ]]; then \
		${SHELL} ${TL_TOPDIR}/scripts/git/clean.sh; \
	fi
endef
