# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBBPF=[y|n]
# - LIBBPF_MAJOR_VERSION=
# - LIBBPF_MINOR_VERSION=
#
ifndef _BPF_LIBBPF_MK
export _BPF_LIBBPF_MK = 1

include ldconfig.mk

private-libbpf-paths := $(shell ${LDCONFIG} -p | grep libbpf.so | awk '{print $$NF}' || true)

ifneq (${private-libbpf-paths},)
  private-libpf-path := $(shell dirname $(private-libbpf-paths) | sort -u || true)
endif

ifneq (${private-libpf-path},)
  # Like /usr/lib64/libbpf.so.0.4.0
  private-libbpf-v-path := $(shell realpath ${private-libpf-path}/libbpf.so.[0-9])
endif

ifneq (${private-libbpf-v-path},)
  export LIBBPF_MAJOR_VERSION := $(shell echo ${private-libbpf-v-path} | awk -F '.' '{print $$3}')
  export LIBBPF_MINOR_VERSION := $(shell echo ${private-libbpf-v-path} | awk -F '.' '{print $$4}')

  ifeq (${LIBBPF_MAJOR_VERSION},)
    $(error "Could not get libbpf LIBBPF_MAJOR_VERSION")
  endif
  ifeq (${LIBBPF_MINOR_VERSION},)
    $(error "Could not get libbpf LIBBPF_MINOR_VERSION")
  endif

  export HAVE_LIBBPF := y
else
  export HAVE_LIBBPF := n
endif

ifdef DEBUG
  $(info HAVE_LIBBPF = ${HAVE_LIBBPF})
  $(info private-libbpf-paths = ${private-libbpf-paths})
  $(info private-libpf-path = ${private-libpf-path})
  $(info private-libbpf-v-path = ${private-libbpf-v-path})
  $(info LIBBPF_MAJOR_VERSION = ${LIBBPF_MAJOR_VERSION})
  $(info LIBBPF_MINOR_VERSION = ${LIBBPF_MINOR_VERSION})
endif

endif
