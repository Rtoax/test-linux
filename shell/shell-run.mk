# SPDX-License-Identifier: GPL-3.0
Q ?= @

SCRIPTS := $(shell find -name '*.sh' -executable)
LOGS := $(patsubst %.sh,%.log,$(SCRIPTS))

.PHONY: build
build: ${LOGS}
	@echo -e " \033[1;32m Done\033[m: ${SCRIPTS}"

%.log: %.sh
	@echo -e "  RUN  \033[1;32m$(@)\033[m"
	$(Q)${SHELL} $(<) $(ARGS_$(*)) | tee $(@)

.PHONY: test
test:
	@echo -e "  TEST  \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(LOGS)\033[m"
	${Q}rm -f ${LOGS}
