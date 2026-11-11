# SPDX-License-Identifier: GPL-3.0
#
# Syntax:
# $(strip STRING)

ifneq ($(strip AAA BBB     CCC    DDDD),AAA BBB CCC DDDD)
  $(error "strip failed")
endif

.PHONY: build
build:
