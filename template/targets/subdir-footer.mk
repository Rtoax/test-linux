# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
ifndef _TARGET_SUBDIR_FOOTER_MK
_TARGET_SUBDIR_FOOTER_MK = 1

include dir.mk
include verbose.mk
include emoji.mk
include mkflags.mk
include make.mk

ifneq ($(ERROR_ABORT),)
  define _exit
    exit ${1}
  endef
else
  define _exit
  endef
endif

# $1: 'build' or 'clean'
# $2: subdirectory name
define make_sub_dir
  $(call log_info,${1} $(call strip_topdir_prefix,$(2)))
  $(Q)pushd $(2) >/dev/null || exit 1; \
  start_ms=$$(date +%s%3N); \
  DRY_RUN=${DRY_RUN} ${MAKE} ${1} ${SUBMKFLAGS}; \
  makeret=$$?; \
  end_ms=$$(date +%s%3N); \
  cost_ms=$$((end_ms - start_ms)); \
  if [ $${makeret} -ne 0 ]; then \
    $(call log_fail,${EMOJI_CROSS} Failed ${1} $(call strip_topdir_prefix,$(2)) cost $${cost_ms} ms); \
    $(call _exit,${makeret}) \
  else  \
    $(call log_success,${EMOJI_CHECK} Success ${1} $(call strip_topdir_prefix,$(2)) cost $${cost_ms} ms); \
  fi; \
  popd >/dev/null
endef

define make_subdir_build
  $(call make_sub_dir,build,${1})
endef

define make_subdir_clean
  $(call make_sub_dir,clean,${1})
endef

.PHONY: $(subdir-y-build)
$(subdir-y-build):
	$(call log_obj,PUSHD,$(call strip_topdir_prefix,$(patsubst %.build,%,$(@))))
	$(call make_subdir_build,$(@:.build=))

.PHONY: $(subdir-y-clean)
$(subdir-y-clean):
	$(call log_obj,PUSHD,$(call strip_topdir_prefix,$(patsubst %.clean,%,$(@))))
	$(call make_subdir_clean,$(@:.clean=))
endif
