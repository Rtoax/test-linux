# SPDX-License-Identifier: GPL-3.0
#
# $(eval ...)
#

define target
${1}:
	@echo Make ${1}
endef

.PHONY: build
build: rong tao

$(eval $(call target,rong))
$(eval $(call target,tao))
