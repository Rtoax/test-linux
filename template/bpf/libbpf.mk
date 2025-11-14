# SPDX-License-Identifier: GPL-3.0
_LIBBPF = 1

LDCONFIG ?= ldconfig
LIBBPF_PATHES ?= $(shell ${LDCONFIG} -p | grep libbpf.so | awk '{print $$NF}' || true)
LIBBPF_PATH ?= $(shell dirname $(LIBBPF_PATHES) | sort -u || true)
# Like /usr/lib64/libbpf.so.0.4.0
LIBBPF_V_PATH := $(shell realpath ${LIBBPF_PATH}/libbpf.so)

LIBBPF_MAJOR_VERSION := $(shell echo ${LIBBPF_V_PATH} | awk -F '.' '{print $$3}')
LIBBPF_MINOR_VERSION := $(shell echo ${LIBBPF_V_PATH} | awk -F '.' '{print $$4}')

ifdef DEBUG
  $(info LIBBPF_PATHES = ${LIBBPF_PATHES})
  $(info LIBBPF_PATH = ${LIBBPF_PATH})
  $(info LIBBPF_V_PATH = ${LIBBPF_V_PATH})
  $(info LIBBPF_MAJOR_VERSION = ${LIBBPF_MAJOR_VERSION})
  $(info LIBBPF_MINOR_VERSION = ${LIBBPF_MINOR_VERSION})
endif

ifeq (${LIBBPF_MAJOR_VERSION},)
  $(error "Could not get libbpf LIBBPF_MAJOR_VERSION")
endif
ifeq (${LIBBPF_MINOR_VERSION},)
  $(error "Could not get libbpf LIBBPF_MINOR_VERSION")
endif

export LIBBPF_MAJOR_VERSION LIBBPF_MINOR_VERSION LIBBPF_PATH
