# SPDX-License-Identifier: GPL-3.0
Q ?= @

define make_sub_dir
	@make -C ${1} || echo "Failed ${1}" | tee --append ${TL_FAILED_LOG}
endef

$(sub-dir-build):
	@echo -e "\033[1;32m[build] $(patsubst %.build,%,$(@))\033[m"
	${Q}$(call make_sub_dir,$(@:.build=))

$(sub-dir-test):
	@echo -e "\033[1;32m[test] $(patsubst %.test,%,$(@))\033[m"
	${Q}make -C $(@:.test=) test

$(sub-dir-clean):
	@echo -e "\033[1;32m[clean] $(patsubst %.clean,%,$(@))\033[m"
	${Q}make -C $(@:.clean=) clean
