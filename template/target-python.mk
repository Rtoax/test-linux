# SPDX-License-Identifier: GPL-3.0
PYTHON ?= python
Q ?= @

# see TARGETS_PYTHON_LOGS
%.py.log: %.py
	@echo -e "  SHELL  \033[1;32m$(@)\033[m"
	$(Q)${PYTHON} $(<) $(ARGS_$(*)) $(PY_ARGS_$(<)) | tee $(@)
