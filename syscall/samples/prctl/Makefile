# SPDX-License-Identifier: GPL-3.0
include ../../../template/kconfig.mk

target-y := PR_CAPBSET_DROP
target-y += PR_GET_NAME
target-y += PR_SET_VMA_ANON_NAME
target-y += PR_GET_ENDIAN
target-y += PR_SET_SECCOMP

ifeq ($(CONFIG_ANON_VMA_NAME),y)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

include ../../../template/main.mk

PR_CAPBSET_DROP: PR_CAPBSET_DROP.o
PR_GET_NAME: PR_GET_NAME.o
PR_SET_VMA_ANON_NAME: PR_SET_VMA_ANON_NAME.o
PR_GET_ENDIAN: PR_GET_ENDIAN.o
PR_SET_SECCOMP: PR_SET_SECCOMP.o
