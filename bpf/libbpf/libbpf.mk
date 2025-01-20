# SPDX-License-Identifier: GPL-3.0

LIBBPF_PATHS := $(shell ldconfig -p | grep libbpf.so | awk '{print $$NF}' || true)
LIB_PATH := $(shell dirname $(LIBBPF_PATHS) | uniq || true)
# Like /usr/lib64/libbpf.so.0.4.0
LIBBPF_V_PATH := $(shell realpath ${LIB_PATH}/libbpf.so)

LIBBPF_MAJOR_VERSION := $(shell echo ${LIBBPF_V_PATH} | awk -F '.' '{print $$3}')
LIBBPF_MINOR_VERSION := $(shell echo ${LIBBPF_V_PATH} | awk -F '.' '{print $$4}')

export LIBBPF_MAJOR_VERSION LIBBPF_MINOR_VERSION

$(info LIBBPF_PATHS = ${LIBBPF_PATHS})
$(info LIB_PATH = ${LIB_PATH})
$(info LIBBPF_V_PATH = ${LIBBPF_V_PATH})
$(info LIBBPF_MAJOR_VERSION = ${LIBBPF_MAJOR_VERSION})
$(info LIBBPF_MINOR_VERSION = ${LIBBPF_MINOR_VERSION})

