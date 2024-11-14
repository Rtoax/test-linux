# SPDX-License-Identifier: GPL-3.0
SHELL = bash

# Get all .sh suffix scripts
SCRIPTS := $(shell ls *.sh)
# Output .sh.log suffix file list
SCRIPTS_OUT = $(foreach s,${SCRIPTS},${s}.log)

.PHONY: build
build: ${SCRIPTS_OUT}
	@echo -e " \033[1;33m Done \033[m"

.PHONY: test
test: ${SCRIPTS_OUT}
	@echo
	@echo "Test Done"

${SCRIPTS_OUT}: %:
	@echo "Testing \033[1;32m$(basename $(@))\033[m"
	# Strip suffix and execute
	./$(basename $(@)) | tee $(@)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m${SCRIPTS_OUT}\033[m"
	@rm -f ${SCRIPTS_OUT}
