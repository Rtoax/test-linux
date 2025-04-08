# SPDX-License-Identifier: GPL-3.0
#
# test-linux Makefile
# Wrote by Rong Tao <rtoax@foxmail.com>
#
VERSION = 2
PATCHLEVEL = 2
SUBLEVEL = 9
EXTRAVERSION = -rc8
NAME = ET

include make.list
SUB_USER_DIR = $(USER_LIST)
SUB_USER_DIR_TEST := $(SUB_USER_DIR:%=%_test)
SUB_USER_DIR_CLEAN := $(SUB_USER_DIR:%=%_clean)

SUB_KERN_DIR = $(KERNEL_LIST)
SUB_KERN_DIR_TEST := $(SUB_KERN_DIR:%=%_test)
SUB_KERN_DIR_CLEAN := $(SUB_KERN_DIR:%=%_clean)

TEST_LINUX_VERSION = $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
export VERSION PATCHLEVEL SUBLEVEL TEST_LINUX_VERSION

TLCONFIG_CONFIG ?= .config
export TLCONFIG_CONFIG

.PHONY: build
# Default to display help information
build: help

include tlbuild.mk
include kernel.mk
include $(TL_TOPDIR)/scripts/emoji.mk
include $(TL_TOPDIR)/scripts/git.mk
include $(TL_TOPDIR)/scripts/logos.mk

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
	@echo >&2 -e "*** FAILED_LOG ${FAILED_LOG}"
	@echo >&2 -e "*** TEST_LINUX_VERSION ${TEST_LINUX_VERSION}"
	@echo >&2 -e "*** KERNEL_VERSION ${KVERSION}.${KPATCHLEVEL}.${KSUBLEVEL}, CODE ${KVERSION_CODE}"
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

# make_build [U|K] [dir]
define make_build
	@echo -e "[$(1)] \033[1;34mMake [$(2)] starting\033[m"
	@pushd $(2) >/dev/null ; \
		make; \
		if [ $$? -ne 0 ]; then \
			if [ $(1) == U ]; then \
				echo "Failed $(1) $(2)" | tee --append $(FAILED_LOG); \
			elif [ $(1) == K ]; then \
				echo "Failed $(1) $(2)" | tee --append $(FAILED_LOG); \
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
	$(call tl_log,top-makefile all)

.PHONY: default
default: user kernel

.PHONY: user
user: cleanfailedlog $(SUB_USER_DIR)
	$(call tl_log,top-makefile user)
	@echo "=========== User done ==========="
	$(call printfailedlog)
	@echo "${MOONLIGHT}"
$(SUB_USER_DIR):
	$(call make_build,U,$@)

.PHONY: kernel
kernel: cleanfailedlog $(SUB_KERN_DIR)
	@echo "=========== Kernel done ==========="
	$(call printfailedlog)
	@echo "${MOONLIGHT}"
$(SUB_KERN_DIR):
	$(call make_build,K,$@)

.PHONY: test
test: testuser testkernel
testuser:$(SUB_USER_DIR_TEST)
$(SUB_USER_DIR_TEST):
	$(call make_test,U,$(@:%_test=%))
testkernel:$(SUB_KERN_DIR_TEST)
$(SUB_KERN_DIR_TEST):
	$(call make_test,K,$(@:%_test=%))

define installdeps
	${SHELL} scripts/install-deps.sh --all --force
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
	${SHELL} scripts/invalid-link.sh
	@echo "Check invalid symbol link done"
endef

.PHONY: check
check:
	$(call check_links)

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

cleanfailedlog:
	$(call cleanfailedlog)

.PHONY: all test clean \
	$(SUB_USER_DIR) \
	$(SUB_USER_DIR_TEST) \
	$(SUB_USER_DIR_CLEAN) \
	$(SUB_KERN_DIR) \
	$(SUB_KERN_DIR_TEST) \
	$(SUB_KERN_DIR_CLEAN)
