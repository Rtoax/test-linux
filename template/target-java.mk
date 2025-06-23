# SPDX-License-Identifier: GPL-3.0
JAVA ?= $(shell which java 2>/dev/null)
JAVAC ?= $(shell which javac 2>/dev/null)

ifneq (${TARGETS_JAVA},)
  ifeq ($(wildcard $(JAVAC)),)
    $(error Please install java)
  endif
endif

${TARGETS_JAVA}:
	@echo -e "  JAVAC  \033[1;32m$(@)\033[m"
	${Q}$(JAVAC) $(^)
