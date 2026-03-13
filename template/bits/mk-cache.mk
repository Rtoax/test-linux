# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _BITS_MK_CACHE_MK
_BITS_MK_CACHE_MK = 1

# $1: variable append to cache file
# $2: cache file name
define mk_cache_var
$(eval $(shell echo "export ${1} := ${${1}}" >> ${2}))
endef

endif
