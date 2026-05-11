# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - HAVE_PODMAN=[y|n]
# - PODMAN=[/usr/bin/podman]
#
ifndef _PODMAN_MK
_PODMAN_MK = 1

include define.mk

$(call find_cmd_and_def,podman)

endif
