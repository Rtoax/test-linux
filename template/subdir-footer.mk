# SPDX-License-Identifier: GPL-3.0
Q ?= @

# $1: build, test, clean
# $2: sub-dir
define make_sub_dir
	$(call tl_log,"${1} $(call git_relative_dir,$(2))")
	@make -C ${2} || echo "Failed ${1} $(call git_relative_dir,$(2))" | tee --append ${TL_FAILED_LOG}
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

$(sub-dir-build):
	$(call log_tgt_start,build,$(call git_relative_dir,$(patsubst %.build,%,$(@))))
	${Q}$(call make_sub_dir_build,$(@:.build=))

$(sub-dir-test):
	$(call log_tgt_start,test,$(call git_relative_dir,$(patsubst %.test,%,$(@))))
	${Q}$(call make_sub_dir_test,$(@:.test=))

$(sub-dir-clean):
	$(call log_tgt_start,clean,$(call git_relative_dir,$(patsubst %.clean,%,$(@))))
	${Q}$(call make_sub_dir_clean,$(@:.clean=))
