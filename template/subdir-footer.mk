# SPDX-License-Identifier: GPL-3.0

Q ?= @

$(sub-dir-build):
	@echo -e "\033[1;32m[build] $(patsubst %.build,%,$(@))\033[m"
	${Q}@make -C $(@:.build=)

$(sub-dir-test):
	@echo -e "\033[1;32m[test] $(patsubst %.test,%,$(@))\033[m"
	${Q}make -C $(@:.test=) test

$(sub-dir-clean):
	@echo -e "\033[1;32m[clean] $(patsubst %.clean,%,$(@))\033[m"
	${Q}make -C $(@:.clean=) clean
