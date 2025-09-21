# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
_SUDO = 1

# If command require superuser privileges to be executed. Otherwise, EPERM
# will occur. Here, it is detected whether ordinary users are exempt from
# sudo passwords. If so, it is necessary to add the "sudo" prefix to the
# required bpftool command execution.
SUDO := $(shell if sudo --non-interactive true 2>/dev/null; then \
		echo sudo; fi)

ifdef DEBUG
  $(info SUDO = ${SUDO})
endif
