# SPDX-License-Identifier: GPL-3.0
#
# test-linux Makefile
# Wrote by Rong Tao <rtoax@foxmail.com>
#
# Change the CHANGELOG.md at the same time
VERSION = 2
PATCHLEVEL = 2
SUBLEVEL = 15
EXTRAVERSION =
NAME = Java

TEST_LINUX_VERSION := $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
export VERSION PATCHLEVEL SUBLEVEL TEST_LINUX_VERSION

include tlbuild.mk
include kconfig.mk
include kernel.mk
include $(TL_TOPDIR)/scripts/emoji.mk
include $(TL_TOPDIR)/scripts/git.mk
include $(TL_TOPDIR)/scripts/logo.mk

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
	$(call tl_log,top-makefile help)
	@echo >&2 -e "***"
	$(call tl_ascii_logo1,*** )
	@echo >&2 -e "***"
	@echo >&2 -e "*** ${MOONLIGHT} ${MOONLIGHT}"
	@echo >&2 -e "*** TL_TOPDIR ${TL_TOPDIR}"
	@echo >&2 -e "*** GIT_TOPDIR ${GIT_TOPDIR}"
	@echo >&2 -e "***    core.hooksPath = ${GIT_CONFIG_CORE_HOOKSPATH}"
	@echo >&2 -e "*** TL_LOG ${TL_LOG}"
	@echo >&2 -e "*** TL_FAILED_LOG ${TL_FAILED_LOG}"
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

TARGETS_PREP := cleanfailedlog
TARGETS_POST := printfailedlog

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
	$(call installdeps)

.PHONY: install
install: uninstall
	@echo "Install"
	${Q}sudo ln -s ${TL_TOPDIR}/scripts/git/bigfile.sh /usr/bin/git-bigfile
	${Q}sudo ln -s ${TL_TOPDIR}/scripts/git/statistic.sh /usr/bin/git-statistic
	${Q}sudo ln -s ${TL_TOPDIR}/scripts/git/statistic.py /usr/bin/git-statistic.py
	${Q}sudo ln -s ${TL_TOPDIR}/scripts/patchset.sh /usr/bin/patchset

.PHONY: uninstall
uninstall:
	@echo "Uninstall"
	${Q}sudo rm -f /usr/bin/git-bigfile \
		/usr/bin/git-statistic \
		/usr/bin/git-statistic.py \
		/usr/bin/patchset

.PHONY: docker
docker:
	$(call builddocker)

.PHONY: version
version:
	@echo "v${TEST_LINUX_VERSION} (${NAME})"

.PHONY: archive
archive:
	@echo "=== archive"
	$(call git_archive)

.PHONY: config
config:
	@echo "=== config"
	$(call git_config)

.PHONY: kconfig-display
kconfig-display:
	$(call display_all_kconfig)

.PHONY: menuconfig
menuconfig:
	@echo "=== menuconfig"
	$(SHELL) ./scripts/dialog/main.sh

define check_links
	@echo "Check invalid symbol link start"
	${SHELL} scripts/broken-symlinks.sh
	@echo "Check invalid symbol link done"
endef

.PHONY: check
check:
	$(call check_links)

# Clean git repo useless file and directory
cleangit:
	@echo "=== clean git repo"
	$(call git_clean)

cleanfailedlog:
	$(call cleanfailedlog)
printfailedlog:
	$(call printfailedlog)
