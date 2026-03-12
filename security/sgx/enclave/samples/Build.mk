# SPDX-License-Identifier: GPL-3.0
include intel/linux-sgx.mk

# TODO: link error
#target-y := app

target-prep-y := enclave_u.c enclave_u.h
target-prep-y += enclave_t.c enclave_t.h

app-objs := enclave_u.o enclave_t.o

CFLAGS := -I/home/rongtao/Git/intel/linux-sgx/common/inc/
CFLAGS += -I/usr/x86_64-intel-sgx/include/tlibc/

LDFLAGS := -lsgx_urts
LDFLAGS += -lsgx_enclave_common
LDFLAGS += /usr/x86_64-intel-sgx/lib64/libsgx_tstdc.a
