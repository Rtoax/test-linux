# SPDX-License-Identifier: GPL-3.0
_TARGET_JAVA_MK = 1

JAVA ?= $(shell which java 2>/dev/null)
JAVAC ?= $(shell which javac 2>/dev/null)

ifneq (${target-java-y},)
  ifeq ($(wildcard $(JAVAC)),)
    $(error Please install java)
  endif
endif

${target-java-y}:
	$(call log_exe,JAVAC,$(<),$(@))
	${Q}$(JAVAC) $(^)
