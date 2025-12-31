# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Output definitions:
# - SUDO=sudo
# - SUDO_NON_INTERACTIVE=y
#
_SUDO_MK = 1

# If command require superuser privileges to be executed. Otherwise, EPERM
# will occur. Here, it is detected whether ordinary users are exempt from
# sudo passwords. If so, it is necessary to add the "sudo" prefix to the
# required bpftool command execution.
SUDO := $(shell if sudo --non-interactive true 2>/dev/null; then \
		echo sudo; fi)

ifneq (${SUDO},)
  SUDO_NON_INTERACTIVE := y
else
  $(warning "sudo need password, you need to edit /etc/sudoers with NOPASSWD:")
endif

ifdef DEBUG
  $(info SUDO = ${SUDO})
  $(info SUDO_NON_INTERACTIVE = ${SUDO_NON_INTERACTIVE})
endif

export SUDO SUDO_NON_INTERACTIVE
