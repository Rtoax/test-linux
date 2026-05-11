# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - OPENSSL=[/usr/bin/openssl]
# - HAVE_OPENSSL=[y|n]
# - OPENSSL_{VERSION,MAJOR,MINOR,PATCH}=
#
ifndef _OPENSSL_MK
_OPENSSL_MK = 1

include define.mk

$(call find_cmd_and_def,openssl)

ifneq (${OPENSSL},)

include dir.mk

sslversh = ${TOPDIR}/scripts/version/openssl.sh

OPENSSL_VERSION := $(shell ${sslversh})
OPENSSL_MAJOR := $(shell ${sslversh} --major)
OPENSSL_MINOR := $(shell ${sslversh} --minor)
OPENSSL_PATCH := $(shell ${sslversh} --patchlevel)

# $1: output pem file name
define openssl_genrsa
${Q}${OPENSSL} genrsa -out $(1) -3 3072
endef

ifdef DEBUG
  $(info OPENSSL_VERSION ${OPENSSL_VERSION})
  $(info OPENSSL_MAJOR ${OPENSSL_MAJOR})
  $(info OPENSSL_MINOR ${OPENSSL_MINOR})
  $(info OPENSSL_PATCH ${OPENSSL_PATCH})
endif

ifneq (${OPENSSL_VERSION},${OPENSSL_MAJOR}.${OPENSSL_MINOR}.${OPENSSL_PATCH})
  $(error ${OPENSSL_VERSION} != ${OPENSSL_MAJOR}.${OPENSSL_MINOR}.${OPENSSL_PATCH})
endif

export OPENSSL_VERSION OPENSSL_MAJOR OPENSSL_MINOR OPENSSL_PATCH

endif # end of HAVE_OPENSSL

endif
