# SPDX-License-Identifier: GPL-3.0
include amd/rocm.mk

post-${HAVE_HIP} := hipcc-macros.h
