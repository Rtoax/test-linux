# SPDX-License-Identifier: GPL-3.0

OPENSSL := openssl

OPENSSL_VERSION := $(shell openssl version | \
		grep -m1 -ow -E '^OpenSSL [0-9]*?.[0-9]*?.[0-9]*?' | \
		awk '{print $$2}' )

OPENSSL_VERSION_MAJOR := $(shell echo ${OPENSSL_VERSION} | awk -F '.' '{print $$1}')
OPENSSL_VERSION_MINOR := $(shell echo ${OPENSSL_VERSION} | awk -F '.' '{print $$2}')
OPENSSL_VERSION_PATCH := $(shell echo ${OPENSSL_VERSION} | awk -F '.' '{print $$3}')

ifdef DEBUG
  $(info OPENSSL_VERSION ${OPENSSL_VERSION})
  $(info OPENSSL_VERSION_MAJOR ${OPENSSL_VERSION_MAJOR})
  $(info OPENSSL_VERSION_MINOR ${OPENSSL_VERSION_MINOR})
  $(info OPENSSL_VERSION_PATCH ${OPENSSL_VERSION_PATCH})
endif

ifneq (${OPENSSL_VERSION},${OPENSSL_VERSION_MAJOR}.${OPENSSL_VERSION_MINOR}.${OPENSSL_VERSION_PATCH})
  $(error openssl.mk: ${OPENSSL_VERSION} != ${OPENSSL_VERSION_MAJOR}.${OPENSSL_VERSION_MINOR}.${OPENSSL_VERSION_PATCH})
endif
