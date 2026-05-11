# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - KUBELET=[/usr/bin/kubelet]
# - HAVE_KUBELET=[y|n]
# - HAVE_K8S=[y|n]
#
ifndef _K8S_MK
_K8S_MK = 1

include define.mk

$(call find_cmd_and_def,kubelet)

ifeq ($(wildcard ${KUBELET}),)
  HAVE_K8S := n
else
  HAVE_K8S := y
endif

ifdef DEBUG
  $(info HAVE_K8S = ${HAVE_K8S})
endif

export KUBELET
export HAVE_K8S

endif
