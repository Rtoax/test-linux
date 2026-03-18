# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Note:
# - libbpf commit 8ade99a6f84d ("libbpf: Make libbpf_version.h non-auto-generated")
#   v0.6.0 add macro LIBBPF_MAJOR_VERSION and LIBBPF_MINOR_VERSION in
#   libbpf_version.h
#
# Output definitions:
# - HAVE_LIBBPF=[y|n]
# - LIBBPF_MAJOR_VERSION=
# - LIBBPF_MINOR_VERSION=
# - LIBBPF_PATCHLEVEL_VERSION=
# - libbpf-cflags=
#
ifndef _BPF_LIBBPF_MK
_BPF_LIBBPF_MK = 1

include dir.mk

libbpfversh = ${TOPDIR}/scripts/version/libbpf.sh

LIBBPF_VERSION := $(shell ${libbpfversh})

ifeq (${LIBBPF_VERSION},)
  export HAVE_LIBBPF := n
else

export LIBBPF_MAJOR_VERSION := $(shell ${libbpfversh} --major)
export LIBBPF_MINOR_VERSION := $(shell ${libbpfversh} --minor)
export LIBBPF_PATCHLEVEL_VERSION := $(shell ${libbpfversh} --patchlevel)

ifeq (${LIBBPF_MAJOR_VERSION},)
  $(error "Could not get libbpf LIBBPF_MAJOR_VERSION")
endif
ifeq (${LIBBPF_MINOR_VERSION},)
  $(error "Could not get libbpf LIBBPF_MINOR_VERSION")
endif

libbpf-cflags += -DLIBBPF_MAJOR_VERSION=${LIBBPF_MAJOR_VERSION}
libbpf-cflags += -DLIBBPF_MINOR_VERSION=${LIBBPF_MINOR_VERSION}

export HAVE_LIBBPF := y
export libbpf-cflags

endif # end of Found libbpf

ifdef DEBUG
  $(info HAVE_LIBBPF = ${HAVE_LIBBPF})
  $(info LIBBPF_VERSION = ${LIBBPF_VERSION})
  $(info LIBBPF_MAJOR_VERSION = ${LIBBPF_MAJOR_VERSION})
  $(info LIBBPF_MINOR_VERSION = ${LIBBPF_MINOR_VERSION})
  $(info LIBBPF_PATCHLEVEL_VERSION = ${LIBBPF_PATCHLEVEL_VERSION})
  $(info libbpf-cflags = ${libbpf-cflags})
endif

endif # end of _BPF_LIBBPF_MK
