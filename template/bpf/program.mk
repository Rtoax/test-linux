# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Definitions:
# - SUPPORT_BPF_PROG_TYPE_<prog-type>=[y|n]
#
ifndef _BPF_PROGRAM_MK
_BPF_PROGRAM_MK = 1

include bpf/bpf.mk
include bpf/bpftool.mk
include kernel.mk
include dir.mk
include string.mk
include file.mk

# Use cache first if it's exist, because it's fast,
cachefile := ${TOPDIR}/template/bpf/.program.mk.cache
origfile := ${TOPDIR}/template/bpf/program.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else

include bits/mk-cache.mk

$(call make_gen_cachefile,${cachefile})

# $1 - prog name in lowercase
# $2 - prog name in uppercase
define ___bpf_def_prog
  export SUPPORT_BPF_PROG_TYPE_$(2) := y
  bpf-prog-cflags += -DSUPPORT_BPF_PROG_TYPE_$(2)=1
  $(if $(DEBUG),$(info Support $(1) and define SUPPORT_BPF_PROG_TYPE_$(2)))
endef
define bpf_def_prog
  $(eval $(call ___bpf_def_prog,${1},$(call toupper_shell,${1})))
  $(call make_append_var_to_file,SUPPORT_BPF_PROG_TYPE_$(call toupper_shell,${1}),${cachefile})
endef

# linux v6.3-rc6-1646-gfd9c663b9ad6
# commit fd9c663b9ad6 ("bpf: minimal support for programs hooked into netfilter framework")
ifeq ($(call kver_ge,6,3,0),y)
  $(call bpf_def_prog,netfilter)
endif

$(call make_append_var_to_file,bpf-prog-cflags,${cachefile})

endif # end of include cache file

ifdef DEBUG
  $(info bpf-prog-cflags = ${bpf-prog-cflags})
endif

endif
