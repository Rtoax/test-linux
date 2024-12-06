# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


.PHONY: test
test:
	@echo -e "  TEST  \033[1;32m$(@)\033[m"
	./swap-two-words.sh
	./gsub.sh

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	${Q}rm -f *.log
