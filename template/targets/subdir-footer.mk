# SPDX-License-Identifier: GPL-3.0
_TARGET_SUBDIR_FOOTER_MK = 1

include verbose.mk
include emoji.mk

ifneq ($(CHECK_ERROR),)
  CHECK_ERROR_EXIT = exit 1;
endif

# $1: build, test, clean
# $2: subdir-y
define make_sub_dir
	$(call log_info,${1} $(call remove_topdir,$(2)))
	$(Q)pushd $(2) >/dev/null; \
	make ${1}; \
	if [ $$? -ne 0 ]; then \
		$(call log_failed,${EMOJI_CROSS} Failed ${1} $(call remove_topdir,$(2))); \
		${CHECK_ERROR_EXIT} \
	else	\
		$(call log_success,${EMOJI_CHECK} Success ${1} $(call remove_topdir,$(2))); \
	fi; \
	popd >/dev/null
endef

define make_sub_dir_build
	$(call make_sub_dir,build,${1})
endef

define make_sub_dir_test
	$(call make_sub_dir,test,${1})
endef

define make_sub_dir_clean
	$(call make_sub_dir,clean,${1})
endef

$(subdir-y-build):
	$(call log_start,sub-build,$(call remove_topdir,$(patsubst %.build,%,$(@))))
	$(call make_sub_dir_build,$(@:.build=))

$(subdir-y-test):
	$(call log_start,sub-test,$(call remove_topdir,$(patsubst %.test,%,$(@))))
	$(call make_sub_dir_test,$(@:.test=))

$(subdir-y-clean):
	$(call log_start,sub-clean,$(call remove_topdir,$(patsubst %.clean,%,$(@))))
	$(call make_sub_dir_clean,$(@:.clean=))
