# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
ifndef _SHELL_MK
_SHELL_MK = 1

SHELL := bash
ifneq ($(CHECK_ERROR),)
  .SHELLFLAGS := -eu -o pipefail -c
endif

ifdef DEBUG
  $(info SHELL = ${SHELL})
endif

endif
