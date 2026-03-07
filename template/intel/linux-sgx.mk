# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# SGX - Software Guard Extensions
# https://github.com/intel/linux-sgx
#
# Ouput definitions:
# - SGX_SIGN=[/usr/bin/sgx_sign]
# - SGX_EDGER8R=[/usr/bin/sgx_edger8r]
#
ifndef _INTEL_LINUX_SGX_MK
export _INTEL_LINUX_SGX_MK = 1

SGX_SIGN := $(shell which sgx_sign 2>/dev/null)
SGX_EDGER8R := $(shell which sgx_edger8r 2>/dev/null)

ifdef DEBUG
  $(info SGX_SIGN = ${SGX_SIGN})
  $(info SGX_EDGER8R = ${SGX_EDGER8R})
endif

endif
