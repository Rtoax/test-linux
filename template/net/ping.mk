# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Functions:
# - host_is_reachable()=[y|n]
#
ifndef _NET_PING_MK
_NET_PING_MK = 1

# $1: DNS or IP
define host_is_reachable
$(shell if timeout 0.5 ping ${1} -c 1 1>/dev/null 2>&1; then echo y; else echo n; fi)
endef

ifneq ($(call host_is_reachable,localhost),y)
  $(error host_is_reachable localhost failed)
endif
ifneq ($(call host_is_reachable,0),y)
  $(error host_is_reachable localhost failed)
endif

# WTF? www.blablabla.com and www.nonsense.com is reachable.
liufangchushengmingdejingcai = $(call host_is_reachable,www.liufangchushengmingdejingcai.com)
ifneq (${liufangchushengmingdejingcai},n)
  $(error host_is_reachable liufangchushengmingdejingcai failed, ${liufangchushengmingdejingcai})
endif

endif # end of _NET_PING_MK
