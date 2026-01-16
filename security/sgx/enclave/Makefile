# SPDX-License-Identifier: GPL-3.0
include intel/linux-sgx.mk

target-y := app

target-prep-y := enclave_u.c enclave_u.h
target-prep-y += enclave_t.c enclave_t.h

CFLAGS := -I/home/rongtao/Git/intel/linux-sgx/common/inc/

include main.mk

app: app.o enclave_u.o enclave_t.o

enclave_u.c: enclave_u.h
enclave_t.c: enclave_t.h

%_u.h:
	$(call log_obj,EDGER8R,$(*),$(@))
	${Q}${SGX_EDGER8R} --untrusted $(*).edl

%_t.h:
	$(call log_obj,EDGER8R,$(*),$(@))
	${Q}${SGX_EDGER8R} --trusted $(*).edl
