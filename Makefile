# SPDX-License-Identifier: GPL-3.0
#
# test-linux Makefile
# Wrote by Rong Tao <rtoax@foxmail.com>
#
# Change the CHANGELOG.md at the same time
VERSION = 2
PATCHLEVEL = 2
SUBLEVEL = 13
EXTRAVERSION =
NAME = HPC

include make.list

kmod-list-test := $(kmod-list:%=%_test)
kmod-list-clean := $(kmod-list:%=%_clean)

TEST_LINUX_VERSION := $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
export VERSION PATCHLEVEL SUBLEVEL TEST_LINUX_VERSION

TLCONFIG_CONFIG ?= .config
export TLCONFIG_CONFIG

.PHONY: build
# Default to display help information
build: help

include tlbuild.mk
include kconfig.mk
include kernel.mk
include $(TL_TOPDIR)/scripts/emoji.mk
include $(TL_TOPDIR)/scripts/git.mk
include $(TL_TOPDIR)/scripts/ansi.mk
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
	@echo >&2 -e "*** make default: show this information"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make [user|kernel]"
	@echo >&2 -e "*** make [test|testuser|testkernel]"
	@echo >&2 -e "*** make [clean|cleanuser|cleankernel|cleangit]"
	@echo >&2 -e "***"
	@echo >&2 -e "*** make archive"
	@echo >&2 -e "*** make config"
	@echo >&2 -e "*** make kconfig-display"
	@echo >&2 -e "*** make check"
	@echo >&2 -e "*** make installdeps"
	@echo >&2 -e "*** make [install|uninstall]"
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

# kern_build [dir]
define kern_build
	@echo -e "[K] \033[1;34mMake [$(1)] starting\033[m"
	@pushd $(1) >/dev/null ; \
		make; \
		if [ $$? -ne 0 ]; then \
			echo "Failed $(1)" | tee --append $(TL_FAILED_LOG); \
			false; \
		fi ; \
		popd >/dev/null
	@echo -e "[K] Make [$(1)] done"
endef

# kern_test [dir]
define kern_test
	@echo -e "[K] \033[1;35mTest [$(1)] starting\033[m"
	@pushd $(1) >/dev/null ; \
		make test ; \
		popd >/dev/null
	@echo -e "[K] Test [$(1)] done"
endef

# kern_clean [dir]
define kern_clean
	@echo -e "[K] \033[1;36mClean [$(1)] starting\033[m"
	@pushd $(1) >/dev/null ; \
		make clean ; \
		popd >/dev/null
	@echo -e "[K] Clean [$(1)] done"
endef

.PHONY: all
all: default ${TLCONFIG_CONFIG}
	$(call tl_log,top-makefile all)

.PHONY: default
default: user kernel

include template/subdir-header.mk

.PHONY: user
user: cleanfailedlog ${sub-dir-build}
	$(call tl_log,top-makefile user)
	@echo "=========== User done ==========="
	$(call printfailedlog)
	@echo "${MOONLIGHT}"

.PHONY: kernel
kernel: cleanfailedlog $(kmod-list)
	@echo "=========== Kernel done ==========="
	$(call printfailedlog)
	@echo "${MOONLIGHT}"
$(kmod-list):
	$(call kern_build,$@)

.PHONY: test
test: testuser testkernel
testuser: ${sub-dir-test}
testkernel:$(kmod-list-test)
$(kmod-list-test):
	$(call kern_test,$(@:%_test=%))

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

define check_links
	@echo "Check invalid symbol link start"
	${SHELL} scripts/broken-symlinks.sh
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
cleanuser: ${sub-dir-clean}
	@echo "=== clean user"
cleankernel: $(kmod-list-clean)
	@echo "=== clean kernel"
$(kmod-list-clean):
	$(call kern_clean,$(@:%_clean=%))
# Clean git repo useless file and directory
cleangit:
	@echo "=== clean git repo"
	$(call git_clean)

cleanfailedlog:
	$(call cleanfailedlog)

include template/subdir-footer.mk

.PHONY: all test clean \
	${sub-dir-build} \
	${sub-dir-test} \
	${sub-dir-clean} \
	$(kmod-list) \
	$(kmod-list-test) \
	$(kmod-list-clean)
