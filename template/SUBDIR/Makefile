# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


.PHONY: all
all:
	@echo -e "  CC  \033[1;33m SUBDIR build \033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;33m SUBDIR clean \033[m"
