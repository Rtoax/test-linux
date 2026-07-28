# SPDX-License-Identifier: GPL-3.0
#
# Definitions:
# - HAVE_PKG_CONFIG=[y]
# - PKG_CONFIG=[/usr/bin/pkg-config]
#
# Functions:
# - pkg_config_cflags()
# - pkg_config_libs()
#
ifndef _PKG_CONFIG_MK
_PKG_CONFIG_MK = 1

include define.mk

$(call find_cmd_and_def,pkg-config)

ifeq (${HAVE_PKG_CONFIG},y)
  # $1: module, such as: json-c
  define pkg_config_cflags
  $(shell ${PKG_CONFIG} --cflags ${1})
  endef
  # $1: module, such as: json-c
  define pkg_config_libs
  $(shell ${PKG_CONFIG} --libs ${1})
  endef
else
  define pkg_config_cflags
  $(warning Not found pkg-config)
  endef
  define pkg_config_libs
  $(warning Not found pkg-config)
  endef
endif

endif
