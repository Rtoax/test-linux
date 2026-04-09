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
SUBLEVEL = 2
EXTRAVERSION =
NAME = Gay

TEST_LINUX_VERSION := $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
TEST_LINUX_GIT_VERSION := $(shell git describe --abbrev=6 --dirty --tags 2>/dev/null || :)
ifeq ($(TEST_LINUX_GIT_VERSION),)
  TEST_LINUX_GIT_VERSION := not-in-git
endif
GIT_HOOKSPATH := $(shell git config get core.hooksPath 2>/dev/null \
				|| git config core.hooksPath 2>/dev/null \
				|| echo "UnsupportGetHooks")
GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)

export VERSION PATCHLEVEL SUBLEVEL NAME TEST_LINUX_VERSION TEST_LINUX_GIT_VERSION

include template/verbose.mk
include template/dir.mk
include template/shell.mk
include template/sudo.mk

# If in git-tree, need check something already config.
ifneq (${GIT_TOPDIR},)
  ifneq (${GIT_HOOKSPATH},scripts/git/hooks/)
    ifeq ($(filter $(MAKECMDGOALS),install uninstall deps),)
      $(error You MUST run 'make install' first!!)
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
  ifeq ($(filter $(MAKECMDGOALS),install deps),)
    $(error You MUST run 'make install' first, then start a new bash session!!)
  endif
endif

ifndef __USE_TEST_LINUX_MAKE__
  ifeq ($(filter $(MAKECMDGOALS),install uninstall),)
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
	@echo >&2 -e "***    core.hooksPath = ${GIT_HOOKSPATH}"
	@echo >&2 -e "*** TEST_LINUX_VERSION v${TEST_LINUX_VERSION}-${NAME} (${TEST_LINUX_GIT_VERSION})"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make build [KMOD=0] [USER=0]"
	@echo >&2 -e "*** make test"
	@echo >&2 -e "*** make clean"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make check"
	@echo >&2 -e "*** make deps"
	@echo >&2 -e "*** make [install|uninstall]"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make menuconfig"
	@echo >&2 -e "*** make config"
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

ifeq ($(filter $(MAKECMDGOALS),install uninstall deps),)
  include template/main.mk
endif

.PHONY: deps
deps:
	@echo "Deps"
	${Q}${SUDO} ${SHELL} ${TOPDIR}/scripts/install-deps.sh --all --force --noupgrade

.PHONY: install
install: uninstall
	@echo "Install"
	${Q}ln -s ${TOPDIR}/ai/pytorch/build/compile /usr/bin/pytorch-compile
	${Q}ln -s ${TOPDIR}/qemu/compile.sh /usr/bin/qemu-compile
	${Q}ln -s ${TOPDIR}/tools/heatmap/hmctl.sh /usr/bin/hmctl
	${Q}${SHELL} ${TOPDIR}/scripts/scripts-install.sh
	${Q}$(SHELL) ${TOPDIR}/scripts/git/hooks/config.sh

.PHONY: uninstall
uninstall:
	@echo "Uninstall"
	${Q}${SHELL} ${TOPDIR}/scripts/scripts-install.sh uninstall
	${Q}rm -f /usr/bin/pytorch-compile \
		/usr/bin/qemu-compile \
		/usr/bin/hmctl

.PHONY: menuconfig
menuconfig:
	@echo "=== menuconfig"
	$(SHELL) ${TOPDIR}/scripts/config/dialog.sh

.PHONY: config
config:
	@echo "=== config"
	$(SHELL) ${TOPDIR}/scripts/config/no-interaction.sh

.PHONY: check
check:
	@echo "Check startup"
	${Q}${SHELL} ${TOPDIR}/scripts/broken-symlinks.sh
	@echo "Check done"

.PHONY: cleangit
cleangit:
	@echo "=== clean git repo"
	${Q}${SHELL} ${TOPDIR}/scripts/git/clean.sh

endif # _TEST_LINUX_MK
