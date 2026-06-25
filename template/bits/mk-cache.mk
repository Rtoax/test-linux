# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - make_append_var_to_file()
#
ifndef _BITS_MK_CACHE_MK
_BITS_MK_CACHE_MK = 1

# Append makefile variable to file and export it.
# $1: variable append to cache file
# $2: cache file name
define make_append_var_to_file
$(eval $(shell echo "export ${1} := ${${1}}" >> ${2}))
endef

endif
