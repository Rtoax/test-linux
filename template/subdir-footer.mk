# SPDX-License-Identifier: GPL-3.0
Q ?= @

ABS_CURRENT_DIR := $(shell realpath .)
GIT_TOP_DIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)
ifneq ($(GIT_TOP_DIR),)
  CURRENT_DIR := $(patsubst ${GIT_TOP_DIR}/%,%,$(ABS_CURRENT_DIR))
else
  CURRENT_DIR := ${ABS_CURRENT_DIR}
endif

define relate_dir
$(patsubst ${GIT_TOP_DIR}/%,%,$(1))
endef

define make_sub_dir_build
	$(call tl_log,"Build $(call relate_dir,$(1))")
	@make -C ${1} || echo "Failed build $(call relate_dir,$(1))" | tee --append ${TL_FAILED_LOG}
endef

define make_sub_dir_test
	$(call tl_log,"Test $(call relate_dir,$(1))")
	@make -C ${1} test || echo "Failed test $(call relate_dir,$(1))" | tee --append ${TL_FAILED_LOG}
endef

define make_sub_dir_clean
	$(call tl_log,"Clean $(call relate_dir,$(1))")
	@make -C ${1} clean || echo "Failed clean $(call relate_dir,$(1))" | tee --append ${TL_FAILED_LOG}
endef

$(sub-dir-build):
	$(call log_tgt_start,build,$(call relate_dir,$(patsubst %.build,%,$(@))))
	${Q}$(call make_sub_dir_build,$(@:.build=))

$(sub-dir-test):
	$(call log_tgt_start,test,$(call relate_dir,$(patsubst %.test,%,$(@))))
	${Q}$(call make_sub_dir_test,$(@:.test=))

$(sub-dir-clean):
	$(call log_tgt_start,clean,$(call relate_dir,$(patsubst %.clean,%,$(@))))
	${Q}$(call make_sub_dir_clean,$(@:.clean=))
