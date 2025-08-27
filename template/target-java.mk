# SPDX-License-Identifier: GPL-3.0
_TARGET_JAVA = 1

JAVA ?= $(shell which java 2>/dev/null)
JAVAC ?= $(shell which javac 2>/dev/null)

ifneq (${targets-java},)
  ifeq ($(wildcard $(JAVAC)),)
    $(error Please install java)
  endif
endif

${targets-java}:
	$(call log_tgt_exe,JAVAC,$(<),$(@))
	${Q}$(JAVAC) $(^)
