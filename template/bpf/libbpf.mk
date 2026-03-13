# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBBPF=[y|n]
# - LIBBPF_MAJOR_VERSION=
# - LIBBPF_MINOR_VERSION=
#
ifndef _BPF_LIBBPF_MK
_BPF_LIBBPF_MK = 1

include ldconfig.mk

libbpf-paths := $(shell ${LDCONFIG} -p | grep libbpf.so | awk '{print $$NF}' || true)

ifneq (${libbpf-paths},)
  libbpf-path := $(shell dirname $(libbpf-paths) | sort -u || true)
endif

ifneq (${libbpf-path},)
  # Like /usr/lib64/libbpf.so.0.4.0
  libbpf-so := $(shell realpath ${libbpf-path}/libbpf.so.[0-9])
endif

ifeq (${libbpf-so},)
  export HAVE_LIBBPF := n
else

  export LIBBPF_MAJOR_VERSION := $(shell echo ${libbpf-so} | awk -F '.' '{print $$3}')
  export LIBBPF_MINOR_VERSION := $(shell echo ${libbpf-so} | awk -F '.' '{print $$4}')

  ifeq (${LIBBPF_MAJOR_VERSION},)
    $(error "Could not get libbpf LIBBPF_MAJOR_VERSION")
  endif
  ifeq (${LIBBPF_MINOR_VERSION},)
    $(error "Could not get libbpf LIBBPF_MINOR_VERSION")
  endif

  export HAVE_LIBBPF := y
endif

ifdef DEBUG
  $(info HAVE_LIBBPF = ${HAVE_LIBBPF})
  $(info libbpf-paths = ${libbpf-paths})
  $(info libbpf-path = ${libbpf-path})
  $(info libbpf-so = ${libbpf-so})
  $(info LIBBPF_MAJOR_VERSION = ${LIBBPF_MAJOR_VERSION})
  $(info LIBBPF_MINOR_VERSION = ${LIBBPF_MINOR_VERSION})
endif

endif
