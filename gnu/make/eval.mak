# SPDX-License-Identifier: GPL-3.0
#
# $(eval ...)
#

define target
${1}:
	@echo Make ${1}
endef

# $1: number
# $2: number
define add_shell
$(shell echo $$((${1} + ${2})))
endef

define def_shell
define ${1}_1
$(call add_shell,1,1)
endef
endef

$(eval $(call def_shell,add))

ifneq ($(call add_1),2)
  $(error Bad add_1 = $(call add_1))
endif

.PHONY: build
build: rong tao

$(eval $(call target,rong))
$(eval $(call target,tao))
