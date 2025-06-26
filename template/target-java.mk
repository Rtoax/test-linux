# SPDX-License-Identifier: GPL-3.0
JAVA ?= $(shell which java 2>/dev/null)
JAVAC ?= $(shell which javac 2>/dev/null)

ifneq (${TARGETS_JAVA},)
  ifeq ($(wildcard $(JAVAC)),)
    $(error Please install java)
  endif
endif

${TARGETS_JAVA}:
	$(call log_tgt_exe,JAVAC,$(<),$(@))
	${Q}$(JAVAC) $(^)
