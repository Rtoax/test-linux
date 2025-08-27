# SPDX-License-Identifier: GPL-3.0
_SUBDIR_FOOTER = 1

Q ?= @

# $1: build, test, clean
# $2: sub-dir
define make_sub_dir
	$(call log_info,${1} $(call git_relative_dir,$(2)))
	$(Q)pushd $(2) >/dev/null; \
	make ${1}; \
	if [ $$? -ne 0 ]; then \
		$(call log_failed,Failed ${1} $(call git_relative_dir,$(2))); \
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

$(sub-dir-build) $(kmod-list-build):
	$(call log_tgt_start,sub-build,$(call git_relative_dir,$(patsubst %.build,%,$(@))))
	$(call make_sub_dir_build,$(@:.build=))

$(sub-dir-test) $(kmod-list-test):
	$(call log_tgt_start,sub-test,$(call git_relative_dir,$(patsubst %.test,%,$(@))))
	$(call make_sub_dir_test,$(@:.test=))

$(sub-dir-clean) $(kmod-list-clean):
	$(call log_tgt_start,sub-clean,$(call git_relative_dir,$(patsubst %.clean,%,$(@))))
	$(call make_sub_dir_clean,$(@:.clean=))
