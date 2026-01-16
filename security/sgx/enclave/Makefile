# SPDX-License-Identifier: GPL-3.0
include intel/linux-sgx.mk

target-prep-y := enclave_u.c

include main.mk

enclave_u.c: enclave_u.h

%_u.c:
	${Q}${SGX_EDGER8R} %.edl
