# SPDX-License-Identifier: GPL-3.0
include kernel.mk
include kconfig.mk

# This system call is present only before Linux 2.6. see create_module(2)
ifeq ($(call kver_lt,2,7,0),y)
  target-y += create_module
endif
target-y += init_module
target-y += finit_module
target-y += delete_module

init_module-objs := kmod_helpers.o
finit_module-objs := kmod_helpers.o
delete_module-objs := kmod_helpers.o

ifeq (${CONFIG_MODULE_FORCE_LOAD},y)
  CFLAGS += -DCONFIG_MODULE_FORCE_LOAD=1
endif

CFLAGS_init_module := -DUSE_MMAP=1
CFLAGS_finit_module := -DTEST_FINIT_MODULE=1
