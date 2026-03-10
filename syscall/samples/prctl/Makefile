# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include kconfig.mk

target-y := PR_CAPBSET_DROP
target-y += PR_GET_NAME
target-y += PR_SET_VMA_ANON_NAME
target-y += PR_GET_ENDIAN
target-y += PR_SET_SECCOMP
target-y += PR_SET_PDEATHSIG
target-y += PR_GET_CHILD_SUBREAPER

ifeq ($(CONFIG_ANON_VMA_NAME),y)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

include main.mk
