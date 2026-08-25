# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Refs:
# - Compiling to BPF with GCC: https://lwn.net/Articles/800606/
# - https://git.sr.ht/~brianwitte/gcc-bpf-example
#   - github fork: https://github.com/Rtoax/gcc-bpf-example
#   - gitee fork: https://gitee.com/rtoax/gcc-bpf-example
# - https://gcc.gnu.org/wiki/BPFBackEnd
#
# Definitions:
# - HAVE_BPF_GCC=[y]
# - BPF_GCC=[/usr/bin/bpf-unknown-none-gcc|/usr/bin/bpf-gcc]
#
ifndef _BPF_GCC_MK
_BPF_GCC_MK = 1

include define.mk

$(call find_cmd_and_def,bpf-unknown-none-gcc,BPF_GCC)
ifneq (${HAVE_BPF_GCC},y)
  $(call find_cmd_and_def,bpf-gcc,BPF_GCC)
endif

endif
