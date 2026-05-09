# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - PODMAN=[/usr/bin/podman]
# - HAVE_PODMAN=[y|n]
#
ifndef _PODMAN_MK
_PODMAN_MK = 1

PODMAN := $(shell which podman 2>/dev/null)
ifeq ($(wildcard ${PODMAN}),)
  HAVE_PODMAN := n
else
  HAVE_PODMAN := y
endif

ifdef DEBUG
  $(info PODMAN = ${PODMAN})
  $(info HAVE_PODMAN = ${HAVE_PODMAN})
endif

export PODMAN
export HAVE_PODMAN

endif
