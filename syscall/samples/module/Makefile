# SPDX-License-Identifier: GPL-3.0
include ../../../kernel.mk
include ../../../template/kconfig.mk

targets :=
# This system call is present only before Linux 2.6. see create_module(2)
ifeq ($(call kernel_lower_than,2,7,0),y)
  targets += create_module
endif
targets += init_module
targets += finit_module
targets += delete_module

ifeq (${CONFIG_MODULE_FORCE_LOAD},y)
  CFLAGS += -DCONFIG_MODULE_FORCE_LOAD=1
endif

CFLAGS_init_module := -DUSE_MMAP=1
CFLAGS_finit_module := -DTEST_FINIT_MODULE=1

ifdef STATIC
  LDFLAGS += -static
endif

include ../../../template/main.mk

mod_helpers.o: mod_helpers.h

create_module: create_module.o
init_module.o: mod_helpers.h
init_module: init_module.o mod_helpers.o
finit_module.o: mod_helpers.h
finit_module: finit_module.o mod_helpers.o
delete_module.o: mod_helpers.h
delete_module: delete_module.o mod_helpers.o
