# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - PROMETHEUS=[/usr/bin/kubelet]
# - HAVE_PROMETHEUS=[y|n]
#
ifndef _PROMETHEUS_MK
_PROMETHEUS_MK = 1

include define.mk

$(call find_cmd_and_def,prometheus)

endif
