# SPDX-License-Identifier: GPL-3.0
include amd/rocm.mk

target-prog-${HAVE_HIP} := version.sh
target-post-${HAVE_HIP} := hipcc-macros.h
