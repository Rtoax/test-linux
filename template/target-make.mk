# SPDX-License-Identifier: GPL-3.0
MAKE := make

%.mk.log: %.mk
	@echo -e "  MK  \033[1;32m$(@)\033[m"
	$(Q)$(MAKE) -f $(<) $(ARGS_$(*)) | tee $(@)
