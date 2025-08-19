# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao
#
# test-linux Makefile
# Wrote by Rong Tao <rtoax@foxmail.com>
#
# Change the CHANGELOG.md at the same time
VERSION = 2
PATCHLEVEL = 3
SUBLEVEL = 2
EXTRAVERSION =
NAME = Qdisc

TEST_LINUX_VERSION := $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
export VERSION PATCHLEVEL SUBLEVEL TEST_LINUX_VERSION

include template/verbose.mk
include template/topdir.mk
include template/emoji.mk
include template/git.mk
include template/ansi.mk
include template/logo.mk
include kconfig.mk
include kernel.mk

GIT_CONFIG_CORE_HOOKSPATH := $(shell git config get core.hooksPath 2>/dev/null \
	|| git config core.hooksPath 2>/dev/null \
	|| echo "UnsupportGetHooks")

# If in git-tree, need check something already config.
ifneq (${GIT_TOPDIR},)
  ifneq (${GIT_CONFIG_CORE_HOOKSPATH},scripts/git/hooks/)
    ifneq ($(firstword $(MAKECMDGOALS)),config)
      $(error You MUST run 'make config' first!!)
    endif
  endif
endif

# Default help
.PHONY: help
help:
	$(call log_info,top-makefile help)
	@echo >&2 -e "***"
	$(call tl_ascii_logo1,*** )
	@echo >&2 -e "***"
	@echo >&2 -e "*** ${MOONLIGHT} ${MOONLIGHT}"
	@echo >&2 -e "*** TOPDIR ${TOPDIR}"
	@echo >&2 -e "*** GIT_TOPDIR ${GIT_TOPDIR}"
	@echo >&2 -e "***    core.hooksPath = ${GIT_CONFIG_CORE_HOOKSPATH}"
	@echo >&2 -e "*** FILE_LOG_INFO ${FILE_LOG_INFO}"
	@echo >&2 -e "*** FILE_LOG_FAILED ${FILE_LOG_FAILED}"
	@echo >&2 -e "*** TEST_LINUX_VERSION v${TEST_LINUX_VERSION} (${NAME})"
	@echo >&2 -e "*** KERNEL_VERSION ${KVERSION}.${KPATCHLEVEL}.${KSUBLEVEL}, CODE ${KVERSION_CODE}"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make build [KMOD=0] [USER=0]"
	@echo >&2 -e "*** make test"
	@echo >&2 -e "*** make clean"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make archive"
	@echo >&2 -e "*** make config"
	@echo >&2 -e "*** make kconfig-display"
	@echo >&2 -e "*** make check"
	@echo >&2 -e "*** make installdeps"
	@echo >&2 -e "*** make [install|uninstall]"
	@echo >&2 -e "*** make docker"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make menuconfig"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make version"
	@echo >&2 -e "***"
	@echo >&2 -e "*** Arguments:"
	@echo >&2 -e "***"
	@echo >&2 -e "***  M32=1  compile with -m32 if possible"
	@echo >&2 -e "***"

include make.list

targets-prep := cleanfailedlog
targets-post := printfailedlog

ifeq ($(KMOD),0)
  kmod-list :=
endif
ifeq ($(USER),0)
  sub-dir :=
endif

include template/main.mk

define installdeps
	${SHELL} scripts/install-deps.sh --all --force --noupgrade
endef

define builddocker
	${SHELL} scripts/build-docker.sh
endef

.PHONY: installdeps
installdeps:
	$(call log_info,top-makefile installdeps)
	$(call installdeps)

.PHONY: install
install: uninstall
	$(call log_info,top-makefile install)
	@echo "Install"
	${Q}ln -s ${TOPDIR}/scripts/git/bigfile.sh /usr/bin/git-bigfile
	${Q}ln -s ${TOPDIR}/scripts/git/statistic.sh /usr/bin/git-statistic
	${Q}ln -s ${TOPDIR}/scripts/git/statistic.py /usr/bin/git-statistic.py
	${Q}ln -s ${TOPDIR}/scripts/git/push-remote-all.sh /usr/bin/git-push-remote-all
	${Q}ln -s ${TOPDIR}/scripts/git/push-remote-all.sh /usr/bin/git-push-remote-all-tags
	${Q}ln -s ${TOPDIR}/scripts/git/rm-permanent.sh /usr/bin/git-rm-permanent
	${Q}ln -s ${TOPDIR}/scripts/patchset.sh /usr/bin/patchset
	${Q}ln -s ${TOPDIR}/scripts/termplot.sh /usr/bin/termplot
	${Q}ln -s ${TOPDIR}/scripts/kconfig_compare.sh /usr/bin/kconfig_compare

.PHONY: uninstall
uninstall:
	$(call log_info,top-makefile uninstall)
	@echo "Uninstall"
	${Q}rm -f /usr/bin/git-bigfile \
		/usr/bin/git-statistic \
		/usr/bin/git-statistic.py \
		/usr/bin/git-push-remote-all \
		/usr/bin/git-push-remote-all-tags \
		/usr/bin/git-rm-permanent \
		/usr/bin/patchset \
		/usr/bin/termplot \
		/usr/bin/kconfig_compare

.PHONY: docker
docker:
	$(call builddocker)

.PHONY: version
version:
	@echo "v${TEST_LINUX_VERSION} (${NAME})"

.PHONY: archive
archive:
	$(call log_info,top-makefile archive)
	@echo "=== archive"
	$(call git_archive)

.PHONY: config
config:
	$(call log_info,top-makefile config)
	@echo "=== config"
	$(call git_config)

.PHONY: kconfig-display
kconfig-display:
	$(call display_all_kconfig)

.PHONY: menuconfig
menuconfig:
	$(call log_info,top-makefile menuconfig)
	@echo "=== menuconfig"
	$(SHELL) ./scripts/dialog/main.sh

define check_links
	@echo "Check invalid symbol link start"
	${SHELL} scripts/broken-symlinks.sh
	@echo "Check invalid symbol link done"
endef

.PHONY: check
check:
	$(call log_info,top-makefile check)
	$(call check_links)

# Clean git repo useless file and directory
cleangit:
	$(call log_info,top-makefile cleangit)
	@echo "=== clean git repo"
	$(call git_clean)

cleanfailedlog:
	$(call cleanfailedlog)
printfailedlog:
	$(call printfailedlog)
