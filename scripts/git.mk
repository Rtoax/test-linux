# SPDX-License-Identifier: GPL-3.0

# Other makefile will include current mk file, then, the include file will not
# exist then.
ifneq ($(wildcard ../tlbuild.mk),)
  include ../tlbuild.mk
endif

define git_config
	@if [[ ! -z $(TL_TOPDIR) ]]; then \
		${SHELL} ${TL_TOPDIR}/scripts/git/config.sh; \
	fi
endef

define git_archive
	@if [[ ! -z $(TL_TOPDIR) ]]; then \
		${SHELL} ${TL_TOPDIR}/scripts/git-archive; \
	fi
endef

define git_clean
	@if [[ ! -z $(TL_TOPDIR) ]]; then \
		${SHELL} ${TL_TOPDIR}/scripts/git/clean.sh; \
	fi
endef
