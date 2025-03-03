# Copyright (C) 2025 CESTC, Co. All rights reserved.
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

CONFIG_KERNEL ?= /boot/config-$(shell uname -r)

ifeq ($(wildcard $(CONFIG_KERNEL)),)
  $(warning "WARNING: Not found ${CONFIG_KERNEL}")
else
  include $(CONFIG_KERNEL)
endif

CC := gcc
CFLAGS :=
# Compile to dynamic library.
CFLAGS_PIC := -fPIC
LDFLAGS :=

TARGETS :=
TARGETS_SO :=

TARGETS += main

TARGETS_SO += libnvdso.so

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g -ggdb
  NVDSO_DEBUG := NVDSO_DEBUG=1
endif

ifdef ANON
  NVDSO_ANON := NVDSO_ANON=1
endif

ifeq (${CONFIG_ANON_VMA_NAME},y)
  $(info INFO: Support CONFIG_ANON_VMA_NAME)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

CFLAGS_main :=
CFLAGS_nvdso := ${CFLAGS_PIC}

.PHONY: all
all: ${TARGETS} ${TARGETS_SO} virt2phy
	@echo -e " \033[1;33m Done \033[m"

main: main.o
libnvdso.so: nvdso.o

virt2phy:
	./virt2phy.sh

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

$(TARGETS_SO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) -shared -fPIC $(LDFLAGS) $(LDFLAGS_$(*))

.PHONY: test
test: ${TARGETS} ${TARGETS_SO}
	$(Q)${NVDSO_DEBUG} ${NVDSO_ANON} LD_PRELOAD=./libnvdso.so ./main

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_SO)\033[m"
	$(Q)rm -f ${TARGETS} ${TARGETS_SO} *.o *.out vdso.elf virt2phy
