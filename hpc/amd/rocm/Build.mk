# SPDX-License-Identifier: GPL-3.0
include amd/rocm.mk

target-post-${HAVE_HIP} := hipcc-macros.h
