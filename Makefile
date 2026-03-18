# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
#
# test-linux Makefile
# Wrote by Rong Tao <rtoax@foxmail.com>
#
# Change the CHANGELOG.md at the same time, and get the statistic of code with
# cloc will be better (add cloc output to commit message).
ifndef _TEST_LINUX_MK
export _TEST_LINUX_MK = 1

VERSION = 2
PATCHLEVEL = 4
SUBLEVEL = 0
EXTRAVERSION =
NAME = Hopper

TEST_LINUX_VERSION := $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
TEST_LINUX_GIT_VERSION := $(shell git describe --abbrev=6 --dirty --tags 2>/dev/null || :)
ifeq ($(TEST_LINUX_GIT_VERSION),)
  TEST_LINUX_GIT_VERSION := not-in-git
endif

export VERSION PATCHLEVEL SUBLEVEL NAME TEST_LINUX_VERSION TEST_LINUX_GIT_VERSION

include template/verbose.mk
include template/dir.mk
include template/git.mk
include template/shell.mk
include template/sudo.mk

# If in git-tree, need check something already config.
ifneq (${GIT_TOPDIR},)
  ifneq (${GIT_CONFIG_CORE_HOOKSPATH},scripts/git/hooks/)
    ifeq ($(filter $(MAKECMDGOALS),install uninstall gitconfig deps),)
      $(error You MUST run 'make gitconfig' first!!)
    endif
  endif
endif

# FIXME: remove this check after a little while.
ifeq ($(shell test -L /etc/profile.d/make_tl.sh && echo yes),yes)
  ifeq ($(filter $(MAKECMDGOALS),uninstall),)
    $(error You MUST run 'make uninstall' and 'make install' first!!)
  endif
endif

ifeq ($(wildcard /usr/bin/patchset),)
  ifeq ($(filter $(MAKECMDGOALS),install gitconfig deps),)
    $(error You MUST run 'make install' first, then start a new bash session!!)
  endif
endif

ifndef __USE_TEST_LINUX_MAKE__
  ifeq ($(filter $(MAKECMDGOALS),install uninstall gitconfig),)
    $(error Must use test-linux make_tl.sh, startup a login shell with `bash -l`)
  endif
else
  include logo.mk
endif

# Default help
.PHONY: help
help:
	$(call logo_linux_tux,*** )
	@echo >&2 -e "***"
	@echo >&2 -e "*** TOPDIR ${TOPDIR}"
	@echo >&2 -e "*** GIT_TOPDIR ${GIT_TOPDIR}"
	@echo >&2 -e "***    core.hooksPath = ${GIT_CONFIG_CORE_HOOKSPATH}"
	@echo >&2 -e "*** TEST_LINUX_VERSION v${TEST_LINUX_VERSION}-${NAME} (${TEST_LINUX_GIT_VERSION})"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make build [KMOD=0] [USER=0]"
	@echo >&2 -e "*** make test"
	@echo >&2 -e "*** make clean"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make gitconfig"
	@echo >&2 -e "*** make check"
	@echo >&2 -e "*** make deps"
	@echo >&2 -e "*** make [install|uninstall]"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make menuconfig"
	@echo >&2 -e "*** make config"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make version"
	@echo >&2 -e "***"
	@echo >&2 -e "*** Arguments:"
	@echo >&2 -e "***"
	@echo >&2 -e "***  V=1           compile with verbose mode"
	@echo >&2 -e "***  DEBUG=1       compile with debug mode"
	@echo >&2 -e "***  ERROR=1       compile with error mode"
	@echo >&2 -e "***  FORCE=1       compile with force mode"
	@echo >&2 -e "***  M32=1         compile with -m32 if possible"
	@echo >&2 -e "***  [PIE|NOPIE]=1 compile pie or not"
	@echo >&2 -e "***  NOSUBDIR=1    skip all sub-directory"
	@echo >&2 -e "***  CHECK_ERROR=1 stop immediately when an error occurs"
	@echo >&2 -e "***"

include make.list

target-prep-y := reset
target-post-y := done

target-shell-y := abbrev.sh
target-shell-y += history.sh
target-shell-y += kconfig.sh

ifeq ($(KMOD),0)
  kmod-list-y :=
endif
ifeq ($(USER),0)
  user-list-y :=
endif

subdir-y := ${kmod-list-y}
subdir-y += ${user-list-y}

ifeq ($(filter $(MAKECMDGOALS),install uninstall gitconfig deps),)
  include template/main.mk
endif

define installdeps
	${SUDO} ${SHELL} scripts/install-deps.sh --all --force --noupgrade
endef

.PHONY: deps
deps:
	@echo "Deps"
	$(call installdeps)

.PHONY: install
install: uninstall
	@echo "Install"
	${Q}ln -s ${TOPDIR}/ai/pytorch/build/compile /usr/bin/pytorch-compile
	${Q}ln -s ${TOPDIR}/qemu/compile.sh /usr/bin/qemu-compile
	${Q}ln -s ${TOPDIR}/init/kernel/compile.sh /usr/bin/kcompile
	${Q}ln -s ${TOPDIR}/tools/heatmap/hmctl.sh /usr/bin/hmctl
	${Q}${SHELL} ${TOPDIR}/scripts/scripts-install.sh

.PHONY: uninstall
uninstall:
	@echo "Uninstall"
	${Q}${SHELL} ${TOPDIR}/scripts/scripts-install.sh uninstall
	${Q}rm -f /usr/bin/pytorch-compile \
		/usr/bin/qemu-compile \
		/usr/bin/kcompile \
		/usr/bin/hmctl

.PHONY: version
version:
	@echo "v${TEST_LINUX_VERSION}-${NAME} (${TEST_LINUX_GIT_VERSION})"

.PHONY: gitconfig
gitconfig:
	@echo "=== gitconfig"
	$(SHELL) scripts/git/hooks/config.sh

.PHONY: menuconfig
menuconfig:
	@echo "=== menuconfig"
	$(SHELL) scripts/config/dialog.sh

.PHONY: config
config:
	@echo "=== config"
	$(SHELL) scripts/config/no-interaction.sh

define check_links
	@echo "Check invalid symbol link start"
	${SHELL} scripts/broken-symlinks.sh
	@echo "Check invalid symbol link done"
endef

.PHONY: check
check:
	@echo "Check"
	$(call check_links)

.PHONY: cleangit
cleangit:
	@echo "=== clean git repo"
	$(call git_clean)

endif # _TEST_LINUX_MK
