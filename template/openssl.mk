# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - OPENSSL_VERSION_{MAJOR,MINOR,PATCH}=
#
ifndef _OPENSSL_MK
_OPENSSL_MK = 1

OPENSSL := openssl

OPENSSL_VERSION := $(shell openssl version | \
		grep -m1 -ow -E '^OpenSSL [0-9]*?.[0-9]*?.[0-9]*?' | \
		awk '{print $$2}' )

OPENSSL_VERSION_MAJOR := $(shell echo ${OPENSSL_VERSION} | awk -F '.' '{print $$1}')
OPENSSL_VERSION_MINOR := $(shell echo ${OPENSSL_VERSION} | awk -F '.' '{print $$2}')
OPENSSL_VERSION_PATCH := $(shell echo ${OPENSSL_VERSION} | awk -F '.' '{print $$3}')

# $1: output pem file name
define openssl_genrsa
${Q}${OPENSSL} genrsa -out $(1) -3 3072
endef

ifdef DEBUG
  $(info OPENSSL_VERSION ${OPENSSL_VERSION})
  $(info OPENSSL_VERSION_MAJOR ${OPENSSL_VERSION_MAJOR})
  $(info OPENSSL_VERSION_MINOR ${OPENSSL_VERSION_MINOR})
  $(info OPENSSL_VERSION_PATCH ${OPENSSL_VERSION_PATCH})
endif

ifneq (${OPENSSL_VERSION},${OPENSSL_VERSION_MAJOR}.${OPENSSL_VERSION_MINOR}.${OPENSSL_VERSION_PATCH})
  $(error ${OPENSSL_VERSION} != ${OPENSSL_VERSION_MAJOR}.${OPENSSL_VERSION_MINOR}.${OPENSSL_VERSION_PATCH})
endif

export OPENSSL_VERSION_MAJOR OPENSSL_VERSION_MINOR OPENSSL_VERSION_PATCH

endif
