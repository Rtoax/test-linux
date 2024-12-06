# SPDX-License-Identifier: GPL-3.0
#
# test-linux Makefile
# Wrote by Rong Tao <rtoax@foxmail.com>
#
VERSION = 2
PATCHLEVEL = 2
SUBLEVEL = 4
EXTRAVERSION =
NAME = Apple

SHELL = bash
ifeq ($(V),1)
  Q =
  MAKEFLAGS += V=1
else
  Q = @
  MAKEFLAGS += --silent
  MAKEFLAGS += --no-print-directory
endif
export Q

ifdef M32
  MAKEFLAGS += M32=1
endif

export MAKEFLAGS
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))

GIT_CONFIG_CORE_HOOKSPATH := $(shell ./scripts/git/config.sh 2>/dev/null || echo "UnsupportGetHooks")

USER_FAILED_LOG := $(shell pwd)/failed-user.log
KERNEL_FAILED_LOG := $(shell pwd)/failed-kernel.log
export USER_FAILED_LOG
export KERNEL_FAILED_LOG

include make.list
SUB_USER_DIR = $(USER_LIST)
SUB_USER_DIR_TEST := $(SUB_USER_DIR:%=%_test)
SUB_USER_DIR_CLEAN := $(SUB_USER_DIR:%=%_clean)

SUB_KERN_DIR = $(KERNEL_LIST)
SUB_KERN_DIR_TEST := $(SUB_KERN_DIR:%=%_test)
SUB_KERN_DIR_CLEAN := $(SUB_KERN_DIR:%=%_clean)

this-makefile := $(lastword $(MAKEFILE_LIST))
ABS_SRCTREE := $(realpath $(dir $(this-makefile)))
export ABS_SRCTREE

TEST_LINUX_VERSION = $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
export VERSION PATCHLEVEL SUBLEVEL TEST_LINUX_VERSION

TLCONFIG_CONFIG ?= .config
export TLCONFIG_CONFIG


.PHONY: build
# Default to display help information
build: help

include $(ABS_SRCTREE)/scripts/tlbuild.mk
include tlbuild.mk

# If in git-tree, need check something already config.
ifneq (${GIT_TOPDIR},)
  ifneq (${GIT_CONFIG_CORE_HOOKSPATH},scripts/git/hooks/)
    ifeq (${GIT_CONFIG_CORE_HOOKSPATH},UnsupportGetHooks)
        $(warning Git not support 'git config [get|set]'!!!)
    else
      ifneq ($(firstword $(MAKECMDGOALS)),config)
        $(error You MUST run 'make config' first!!)
      endif
    endif
  endif
endif

.PHONY: help
help:
	@echo >&2 -e "***"
	$(call tl_ascii_logo1,*** )
	@echo >&2 -e "***"
	@echo >&2 -e "*** ABS_SRCTREE ${ABS_SRCTREE}"
	@echo >&2 -e "*** GIT_TOPDIR ${GIT_TOPDIR}"
	@echo >&2 -e "***    core.hooksPath = ${GIT_CONFIG_CORE_HOOKSPATH}"
	@echo >&2 -e "*** USER_FAILED_LOG ${USER_FAILED_LOG}"
	@echo >&2 -e "*** KERNEL_FAILED_LOG ${KERNEL_FAILED_LOG}"
	@echo >&2 -e "*** TEST_LINUX_VERSION ${TEST_LINUX_VERSION}"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make default: show this information"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make [user|kernel]"
	@echo >&2 -e "*** make [test|testuser|testkernel]"
	@echo >&2 -e "*** make [clean|cleanuser|cleankernel|cleangit]"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make archive"
	@echo >&2 -e "*** make config"
	@echo >&2 -e "*** make check"
	@echo >&2 -e "*** make installdeps"
	@echo >&2 -e "*** make docker"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make version"
	@echo >&2 -e "***"
	@echo >&2 -e "*** Arguments:"
	@echo >&2 -e "***"
	@echo >&2 -e "***  M32=1  compile with -m32 if possible"
	@echo >&2 -e "***"

$(TLCONFIG_CONFIG):
	@echo >&2 -e "***"
	@echo >&2 -e "*** Configuration file "$@" not found!"
	@echo >&2 -e "***"
	@echo >&2 -e "*** Please run some configurator"
	@echo >&2 -e "***"
	@/bin/false

define cleanuserlog
	${Q}rm -f $(USER_FAILED_LOG)
endef
define cleankernellog
	${Q}rm -f $(KERNEL_FAILED_LOG)
endef
define printuserlog
	@if [[ -e $(USER_FAILED_LOG) ]]; then \
		cat $(USER_FAILED_LOG) ; \
	fi
endef
define printkernellog
	@if [[ -e $(KERNEL_FAILED_LOG) ]]; then \
		cat $(KERNEL_FAILED_LOG) ; \
	fi
endef

# make_and_log [U|K] [dir]
define make_and_log
	@echo -e "[$(1)] \033[1;34mMake [$(2)] starting\033[m"
	@pushd $(2) >/dev/null ; \
		make ${SUB_MAKE_USER_ARGS}; \
		if [ $$? -ne 0 ]; then \
			if [ $(1) == U ]; then \
				echo "Failed $(1) $(2)" >>$(USER_FAILED_LOG); \
			elif [ $(1) == K ]; then \
				echo "Failed $(1) $(2)" >>$(KERNEL_FAILED_LOG); \
			fi ; \
			false; \
		fi ; \
		popd >/dev/null
	@echo -e "[$(1)] Make [$(2)] done"
endef

# make_test [U|K] [dir]
define make_test
	@echo -e "[$(1)] \033[1;35mTest [$(2)] starting\033[m"
	@pushd $(2) >/dev/null ; \
		make test ; \
		popd >/dev/null
	@echo -e "[$(1)] Test [$(2)] done"
endef

# make_clean [U|K] [dir]
define make_clean
	@echo -e "[$(1)] \033[1;36mClean [$(2)] starting\033[m"
	@pushd $(2) >/dev/null ; \
		make clean ; \
		popd >/dev/null
	@echo -e "[$(1)] Clean [$(2)] done"
endef

.PHONY: all
all: default ${TLCONFIG_CONFIG}
default: user kernel

.PHONY: user
user: cleanuserlog $(SUB_USER_DIR)
	@echo "=========== User done ==========="
	$(call printuserlog)
$(SUB_USER_DIR):
	$(call make_and_log,U,$@)

.PHONY: kernel
kernel: cleankernellog $(SUB_KERN_DIR)
	@echo "=========== Kernel done ==========="
	$(call printkernellog)
$(SUB_USER_DIR):
$(SUB_KERN_DIR):
	$(call make_and_log,K,$@)

.PHONY: test
test: testuser testkernel
testuser:$(SUB_USER_DIR_TEST)
$(SUB_USER_DIR_TEST):
	$(call make_test,U,$(@:%_test=%))
testkernel:$(SUB_KERN_DIR_TEST)
$(SUB_KERN_DIR_TEST):
	$(call make_test,K,$(@:%_test=%))

define installdeps
	${SHELL} scripts/install-deps.sh --all --allowerasing
endef

define builddocker
	${SHELL} scripts/build-docker.sh
endef

.PHONY: installdeps
installdeps:
	$(call installdeps)

.PHONY: docker
docker:
	$(call builddocker)

.PHONY: version
version:
	@echo "v${VERSION}.${PATCHLEVEL}.${SUBLEVEL}${EXTRAVERSION} (${NAME})"

define git_config
	${SHELL} scripts/git/config.sh
endef

define git_archive
	${SHELL} scripts/git-archive
endef

.PHONY: archive
archive:
	@echo "=== archive"
	$(call git_archive)

.PHONY: config
config:
	@echo "=== config"
	$(call git_config)

define check_links
	@echo "Check invalid symbol link start"
	bash scripts/invalid-link.sh
	@echo "Check invalid symbol link done"
endef

.PHONY: check
check:
	$(call check_links)

define git_clean
	bash scripts/git-clean
endef

.PHONY: clean
clean:
	$(call git_clean)
	@echo "==="
	@echo "=== cleanall"
	@echo "=== cleanuser"
	@echo "=== cleankernel"
	@echo "=== cleangit (default)"
	@echo "==="
cleanall: cleanuser cleankernel cleangit
	@echo "=== clean all"
cleanuser: $(SUB_USER_DIR_CLEAN)
	@echo "=== clean user"
$(SUB_USER_DIR_CLEAN):
	$(call make_clean,U,$(@:%_clean=%))
cleankernel: $(SUB_KERN_DIR_CLEAN)
	@echo "=== clean kernel"
$(SUB_KERN_DIR_CLEAN):
	$(call make_clean,K,$(@:%_clean=%))
# Clean git repo useless file and directory
cleangit:
	@echo "=== clean git repo"
	$(call git_clean)

cleanuserlog:
	$(call cleanuserlog)
cleankernellog:
	$(call cleankernellog)

.PHONY: all test clean \
	$(SUB_USER_DIR) \
	$(SUB_USER_DIR_TEST) \
	$(SUB_USER_DIR_CLEAN) \
	$(SUB_KERN_DIR) \
	$(SUB_KERN_DIR_TEST) \
	$(SUB_KERN_DIR_CLEAN)
