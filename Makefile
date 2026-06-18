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
SUBLEVEL = 7
EXTRAVERSION =
NAME = Lamada

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
  $(error You MUST remove /etc/profile.d/make_tl.sh first!!)
endif

ifeq ($(wildcard /usr/bin/make_tl),)
  ifeq ($(filter $(MAKECMDGOALS),install uninstall deps),)
    $(error You MUST run 'make install' first, then start a new bash session!!)
  endif
endif

ifndef __USE_TEST_LINUX_MAKE__
  ifeq ($(filter $(MAKECMDGOALS),install uninstall),)
    $(error Must use test-linux make_tl.sh, `make install` first, then startup a login shell with `bash -l`)
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
	@echo >&2 -e "*** make build [KMOD=<y|n>] [USRC=<y|n>]"
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
	@echo >&2 -e "***  ERROR_STOP=1  stop immediately when an error occurs"
	@echo >&2 -e "***  FORCE=1       compile with force mode"
	@echo >&2 -e "***  M32=1         compile with -m32 if possible"
	@echo >&2 -e "***  [PIE|NOPIE]=1 compile pie or not"
	@echo >&2 -e "***  NOSUBDIR=1    skip all sub-directory"
	@echo >&2 -e "***  TMOUT=1       specify timeout seconds"
	@echo >&2 -e "***  DRY_RUN=1     don't actually make"
	@echo >&2 -e "***"

# default compile kmod and user-source, see also scripts/Makefile.build and
# scripts/Makefile.kmod
KMOD ?= y
USRC ?= y

ifneq (${KMOD}${USRC},)
  subdir-y := $(shell for d in $(call list_dir); do \
                        if [[ -e $$d/Build.mk ]]; then echo "$$d"; fi; done)
endif

target-prep-y := reset
post-y := done

prog-y := abbrev.sh
prog-y += history.sh
prog-y += kconfig.sh

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
	${Q}${SHELL} ${TOPDIR}/scripts/scripts-install.sh
	${Q}$(SHELL) ${TOPDIR}/scripts/git/hooks/config.sh

.PHONY: uninstall
uninstall:
	@echo "Uninstall"
	${Q}${SHELL} ${TOPDIR}/scripts/scripts-install.sh uninstall

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
	${Q}${SHELL} ${TOPDIR}/scripts/docs/linux-reference.sh
	@echo "Check done"

.PHONY: cleangit
cleangit:
	@echo "=== clean git repo"
	${Q}${SHELL} ${TOPDIR}/scripts/git/clean.sh

endif # _TEST_LINUX_MK
