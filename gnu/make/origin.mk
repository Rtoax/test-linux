# SPDX-License-Identifier: GPL-3.0
# origin: where is the variable comes from.

.PHONY: build
build:
	@echo $(origin USER) # environment
	@echo $(origin CC) # default
	@echo $(origin UNDEFINE) # undefined
