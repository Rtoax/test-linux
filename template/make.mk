# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Export:
# - MAKE=[make_tl.sh]
#
# Functions:
# - make_{gt,ge,eq,lt,le}()=[y|n]
# - include_stat()
#
ifndef _MAKE_MK
_MAKE_MK = 1

include ansi.mk
include dir.mk
include version.mk

MAKE := ${TOPDIR}/scripts/make_tl.sh

makeversh = ${TOPDIR}/scripts/version/make.sh

MAKE_VERSION := $(shell ${makeversh})
MAKE_MAJOR := $(shell ${makeversh} --major)
MAKE_MINOR := $(shell ${makeversh} --minor)

$(eval $(call define_version,make,version2_code100010,${MAKE_MAJOR},${MAKE_MINOR}))

# Sometimes including an mk file takes too long, and this function can be
# used to effectively measure the time required to include the mk.
# Set V or DEBUG to enable debug mode.
# Arguments:
# $1: makefile to include
# $2: a random key to identify the makefile for parallelism and nesting
define ___include_stat
  $$(if ${V}${DEBUG},$$(info Including $(1)))
  _start_$(2) := $$(shell date +%s%9N)
  include $(1)
  _end_$(2) := $$(shell date +%s%9N)
  _cost_$(2) := $$(shell expr $$$$( expr $$(_end_$(2)) - $$(_start_$(2)) ) / 1000000)
  $$(if ${V}${DEBUG},$$(info Include $$(call bgreen,$(1)) took $$(call bred,$$(_cost_$(2))) ms))
endef
define include_stat
  $(eval $(call ___include_stat,${1},$(shell mktemp -u XXXXXX)))
endef

ifdef DEBUG
  $(info MAKE = ${MAKE})
  $(info MAKE_VERSION = ${MAKE_VERSION})
  $(info MAKE_MAJOR = ${MAKE_MAJOR})
  $(info MAKE_MINOR = ${MAKE_MINOR})
endif

ifneq ($(call make_ge,4,5), n)
  $(error make_ge failed, $(call make_ge,4,4))
endif

endif
