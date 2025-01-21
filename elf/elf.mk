# SPDX-License-Identifier: GPL-3.0
SHELL = bash

# TODO: 'macro' not equal to '1'?????
define elf_is_pie
  $(shell file $(1) | grep -io pie 1>/dev/null && echo 1)
endef
