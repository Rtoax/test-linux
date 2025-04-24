# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk
include ../../../kernel.mk

TARGETS :=
# This system call is present only before Linux 2.6. see create_module(2)
ifeq ($(call kernel_lower_than,2,7,0),y)
  TARGETS += create_module
endif
TARGETS += init_module
TARGETS += finit_module
TARGETS += delete_module

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

CFLAGS_init_module := -DUSE_MMAP=1
CFLAGS_finit_module := -DTEST_FINIT_MODULE=1

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

mod_helpers.o: mod_helpers.h

create_module: create_module.o
init_module.o: mod_helpers.h
init_module: init_module.o mod_helpers.o
finit_module.o: mod_helpers.h
finit_module: finit_module.o mod_helpers.o
delete_module.o: mod_helpers.h
delete_module: delete_module.o mod_helpers.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
