# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# https://github.com/prometheus/prometheus
#
# Definitions:
# - PROMETHEUS=[/usr/bin/prometheus]
# - HAVE_PROMETHEUS=[y|n]
# - PROMETHEUS_PORT=[9090]
#
ifndef _PROMETHEUS_MK
_PROMETHEUS_MK = 1

include define.mk

$(call find_cmd_and_def,prometheus)

# http://localhost:9090
export PROMETHEUS_PORT := 9090

endif
