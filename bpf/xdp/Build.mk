# SPDX-License-Identifier: GPL-3.0
include bpf/libxdp.mk

subdir-y := samples
subdir-${HAVE_LIBXDP} += libxdp
