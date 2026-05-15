# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - GRAFANA=[/usr/bin/grafana]
# - HAVE_GRAFANA=[y|n]
# - GRAFANA_PORT=[3000]
#
ifndef _GRAFANA_MK
_GRAFANA_MK = 1

include define.mk

$(call find_cmd_and_def,grafana)

# http://localhost:3000
export GRAFANA_PORT := 3000

endif
