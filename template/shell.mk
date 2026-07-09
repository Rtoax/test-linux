# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - SHELL=[bash]
# - .SHELLFLAGS=
#
ifndef _SHELL_MK
_SHELL_MK = 1

SHELL := bash
ifneq ($(ERROR_ABORT),)
  .SHELLFLAGS := -eu -o pipefail -c
endif

ifdef DEBUG
  $(info SHELL = ${SHELL})
endif

export SHELL

endif
