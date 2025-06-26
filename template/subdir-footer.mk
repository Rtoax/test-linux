# SPDX-License-Identifier: GPL-3.0
Q ?= @

define make_sub_dir_build
	$(call tl_log,"Build $(call git_relative_dir,$(1))")
	@make -C ${1} || echo "Failed build $(call git_relative_dir,$(1))" | tee --append ${TL_FAILED_LOG}
endef

define make_sub_dir_test
	$(call tl_log,"Test $(call git_relative_dir,$(1))")
	@make -C ${1} test || echo "Failed test $(call git_relative_dir,$(1))" | tee --append ${TL_FAILED_LOG}
endef

define make_sub_dir_clean
	$(call tl_log,"Clean $(call git_relative_dir,$(1))")
	@make -C ${1} clean || echo "Failed clean $(call git_relative_dir,$(1))" | tee --append ${TL_FAILED_LOG}
endef

$(sub-dir-build):
	$(call log_tgt_start,build,$(call git_relative_dir,$(patsubst %.build,%,$(@))))
	${Q}$(call make_sub_dir_build,$(@:.build=))

$(sub-dir-test):
	$(call log_tgt_start,test,$(call git_relative_dir,$(patsubst %.test,%,$(@))))
	${Q}$(call make_sub_dir_test,$(@:.test=))

$(sub-dir-clean):
	$(call log_tgt_start,clean,$(call git_relative_dir,$(patsubst %.clean,%,$(@))))
	${Q}$(call make_sub_dir_clean,$(@:.clean=))
