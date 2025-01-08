# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

SCRIPTS := $(shell ls *.sh)
LOGS := $(patsubst %.sh,%.log,$(SCRIPTS))

.PHONY: build
build: ${LOGS}
	@echo -e " \033[1;33m Done \033[m"

%.log: %.sh
	@echo -e "  MK  \033[1;32m$(@)\033[m"
	$(Q)${SHELL} $(<) $(ARGS_$(*)) | tee $(@)

.PHONY: test
test:
	@echo -e "  TEST  \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(LOGS)\033[m"
	${Q}rm -f ${LOGS}
