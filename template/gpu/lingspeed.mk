# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output definitions:
# - LSSMI=/usr/bin/ls-smi
# - HAVE_LINGSPEED_GPU=y
# - HAVE_LINGSPEED_X710E=y
# - HAVE_LINGSPEED_X710M=y
# - HAVE_LINGSPEED_X710P=y
#
_GPU_LINGSPEED_MK = 1

LSSMI := $(shell which ls-smi 2>/dev/null)

ifeq ($(wildcard ${LSSMI}),)
  ifndef __IGNORE_NOTFOUND_ERROR__
    $(error No found ls-smi in anywhere)
  else
    LSSMI :=
    $(warning No found ls-smi but __IGNORE_NOTFOUND_ERROR__ defined)
  endif
endif

ifneq ($(LSSMI),)
  ifeq ($(shell ${LSSMI} | grep -oe "X710-E"),X710-E)
    export HAVE_LINGSPEED_X710E := y
  endif
  ifeq ($(shell ${LSSMI} | grep -oe "X710-M"),X710-M)
    export HAVE_LINGSPEED_X710M := y
  endif
  ifeq ($(shell ${LSSMI} | grep -oe "X710-P"),X710-P)
    export HAVE_LINGSPEED_X710P := y
  endif
  ifneq (${HAVE_LINGSPEED_X710E}${HAVE_LINGSPEED_X710M}${HAVE_LINGSPEED_X710P},)
    export HAVE_LINGSPEED_GPU := y
  endif
  export LSSMI
endif

ifdef DEBUG
  $(info LSSMI = ${LSSMI})
  $(info HAVE_LINGSPEED_GPU = ${HAVE_LINGSPEED_GPU})
  $(info HAVE_LINGSPEED_X710E = ${HAVE_LINGSPEED_X710E})
  $(info HAVE_LINGSPEED_X710M = ${HAVE_LINGSPEED_X710M})
  $(info HAVE_LINGSPEED_X710P = ${HAVE_LINGSPEED_X710P})
endif
