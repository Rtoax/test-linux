# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Output definitions:
# - OPENSSL=[/usr/bin/openssl]
# - HAVE_OPENSSL=[y|n]
# - OPENSSL_{VERSION,MAJOR,MINOR,PATCH}=
#
ifndef _OPENSSL_MK
_OPENSSL_MK = 1

include define.mk
include dir.mk
include file.mk

$(call find_cmd_and_def,openssl)

openssl_mk_cachefile := ${TOPDIR}/template/.openssl.mk.cache
openssl_mk_origfile := ${TOPDIR}/template/openssl.mk

ifeq ($(call is_newer,${openssl_mk_cachefile},${openssl_mk_origfile}),y)
  include ${openssl_mk_cachefile}
else

include bits/mk-cache.mk

$(call make_gen_cachefile,${openssl_mk_cachefile})

ifneq (${OPENSSL},)
  sslversh = ${TOPDIR}/scripts/version/openssl.sh

  OPENSSL_VERSION := $(shell ${sslversh})
  OPENSSL_MAJOR := $(shell ${sslversh} --major)
  OPENSSL_MINOR := $(shell ${sslversh} --minor)
  OPENSSL_PATCH := $(shell ${sslversh} --patchlevel)

  # $1: output pem file name
  define openssl_genrsa
  ${Q}${OPENSSL} genrsa -out $(1) -3 3072
  endef

  ifneq (${OPENSSL_VERSION},${OPENSSL_MAJOR}.${OPENSSL_MINOR}.${OPENSSL_PATCH})
    $(error ${OPENSSL_VERSION} != ${OPENSSL_MAJOR}.${OPENSSL_MINOR}.${OPENSSL_PATCH})
  endif

endif # end of HAVE_OPENSSL

$(call make_append_var_to_file,OPENSSL_VERSION,${openssl_mk_cachefile})
$(call make_append_var_to_file,OPENSSL_MAJOR,${openssl_mk_cachefile})
$(call make_append_var_to_file,OPENSSL_MINOR,${openssl_mk_cachefile})
$(call make_append_var_to_file,OPENSSL_PATCH,${openssl_mk_cachefile})

endif # end of cache

export OPENSSL_VERSION OPENSSL_MAJOR OPENSSL_MINOR OPENSSL_PATCH

ifdef DEBUG
  $(info OPENSSL_VERSION ${OPENSSL_VERSION})
  $(info OPENSSL_MAJOR ${OPENSSL_MAJOR})
  $(info OPENSSL_MINOR ${OPENSSL_MINOR})
  $(info OPENSSL_PATCH ${OPENSSL_PATCH})
endif

endif
