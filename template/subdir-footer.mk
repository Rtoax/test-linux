# SPDX-License-Identifier: GPL-3.0
Q ?= @

define make_sub_dir_build
	$(call tl_log,"Build ${1}")
	@make -C ${1} || echo "Failed build ${1}" | tee --append ${TL_FAILED_LOG}
endef

define make_sub_dir_test
	$(call tl_log,"Test  ${1}")
	@make -C ${1} test || echo "Failed test  ${1}" | tee --append ${TL_FAILED_LOG}
endef

define make_sub_dir_clean
	$(call tl_log,"Clean ${1}")
	@make -C ${1} clean || echo "Failed clean ${1}" | tee --append ${TL_FAILED_LOG}
endef

$(sub-dir-build):
	@echo -e "\033[1;32m[build] $(patsubst %.build,%,$(@))\033[m"
	${Q}$(call make_sub_dir_build,$(@:.build=))

$(sub-dir-test):
	@echo -e "\033[1;32m[test] $(patsubst %.test,%,$(@))\033[m"
	${Q}$(call make_sub_dir_test,$(@:.test=))

$(sub-dir-clean):
	@echo -e "\033[1;32m[clean] $(patsubst %.clean,%,$(@))\033[m"
	${Q}$(call make_sub_dir_clean,$(@:.clean=))
