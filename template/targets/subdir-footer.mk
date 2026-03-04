# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_SUBDIR_FOOTER_MK
_TARGET_SUBDIR_FOOTER_MK = 1

include verbose.mk
include emoji.mk
include flags.mk

ifneq ($(CHECK_ERROR),)
  CHECK_ERROR_EXIT = exit 1;
endif

# $1: build, test, clean
# $2: subdir-y
define make_sub_dir
	$(call log_info,${1} $(call strip_topdir_prefix,$(2)))
	$(Q)pushd $(2) >/dev/null; \
	start_ms=$$(date +%s%3N); \
	make ${1} ${SUBMKFLAGS}; \
	makeret=$$?; \
	end_ms=$$(date +%s%3N); \
	cost_ms=$$((end_ms - start_ms)); \
	if [ $${makeret} -ne 0 ]; then \
		$(call log_failed,${EMOJI_CROSS} Failed ${1} $(call strip_topdir_prefix,$(2)) cost $${cost_ms} ms); \
		${CHECK_ERROR_EXIT} \
	else	\
		$(call log_success,${EMOJI_CHECK} Success ${1} $(call strip_topdir_prefix,$(2)) cost $${cost_ms} ms); \
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

.PHONY: $(subdir-y-build)
$(subdir-y-build):
	$(call log_obj,PUSHD,$(call strip_topdir_prefix,$(patsubst %.build,%,$(@))))
	$(call make_sub_dir_build,$(@:.build=))

.PHONY: $(subdir-y-test)
$(subdir-y-test):
	$(call log_obj,PUSHD,$(call strip_topdir_prefix,$(patsubst %.test,%,$(@))))
	$(call make_sub_dir_test,$(@:.test=))

.PHONY: $(subdir-y-clean)
$(subdir-y-clean):
	$(call log_obj,PUSHD,$(call strip_topdir_prefix,$(patsubst %.clean,%,$(@))))
	$(call make_sub_dir_clean,$(@:.clean=))
endif
