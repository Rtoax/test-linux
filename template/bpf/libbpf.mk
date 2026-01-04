# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - LIBBPF_MAJOR_VERSION=
# - LIBBPF_MINOR_VERSION=
#
_BPF_LIBBPF_MK = 1

include ldconfig.mk

private-libbpf-paths ?= $(shell ${LDCONFIG} -p | grep libbpf.so | awk '{print $$NF}' || true)
private-libpf-path ?= $(shell dirname $(private-libbpf-paths) | sort -u || true)
# Like /usr/lib64/libbpf.so.0.4.0
private-libbpf-v-path := $(shell realpath ${private-libpf-path}/libbpf.so.[0-9])

LIBBPF_MAJOR_VERSION := $(shell echo ${private-libbpf-v-path} | awk -F '.' '{print $$3}')
LIBBPF_MINOR_VERSION := $(shell echo ${private-libbpf-v-path} | awk -F '.' '{print $$4}')

ifdef DEBUG
  $(info private-libbpf-paths = ${private-libbpf-paths})
  $(info private-libpf-path = ${private-libpf-path})
  $(info private-libbpf-v-path = ${private-libbpf-v-path})
  $(info LIBBPF_MAJOR_VERSION = ${LIBBPF_MAJOR_VERSION})
  $(info LIBBPF_MINOR_VERSION = ${LIBBPF_MINOR_VERSION})
endif

export LIBBPF_MAJOR_VERSION LIBBPF_MINOR_VERSION

ifeq (${LIBBPF_MAJOR_VERSION},)
  $(error "Could not get libbpf LIBBPF_MAJOR_VERSION")
endif
ifeq (${LIBBPF_MINOR_VERSION},)
  $(error "Could not get libbpf LIBBPF_MINOR_VERSION")
endif
