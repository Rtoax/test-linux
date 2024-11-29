# SPDX-License-Identifier: GPL-3.0
SHELL = bash

include /boot/config-$(shell uname -r)

sub-dir := rss
sub-dir += cache
sub-dir += hugepage
sub-dir += oom
sub-dir += tcmalloc
sub-dir += tlb
sub-dir += jemalloc

TARGETS :=
TARGETS_LIBA :=

TARGETS += virt2phy
TARGETS_LIBA += libtest-linux-mm.a

CC = gcc

CFLAGS :=
LDFLAGS :=

CFLAGS_virt2phy := -DHAVE_MAIN=1
CFLAGS_virt2phy += -DHAVE_LIB_TEST_LINUX_C=1
CFLAGS_virt2phy += -DHAVE_LIB_TEST_LINUX_NUMA=1
CFLAGS_virt2phy += -lnuma

ifeq ($(CONFIG_DEVMEM),y)
  $(info CONFIG_DEVMEM=y)
  CFLAGS_virt2phy += -DCONFIG_DEVMEM=1
endif
# CONFIG_STRICT_DEVMEM=y is the default kernel configuration in general,
# disallows to access RAM area via /dev/mem or only allows first 1MB size
# of RAM.
ifeq ($(CONFIG_STRICT_DEVMEM),y)
  $(warning CONFIG_STRICT_DEVMEM=y, you don't allow r/w from/to /dev/mem)
  CFLAGS_virt2phy += -DCONFIG_STRICT_DEVMEM=1
endif

MAKEFLAGS :=

CFLAGS += -g
export CFLAGS

ifdef DEBUG
  CFLAGS += -DDEBUG=1
  MAKEFLAGS := DEBUG=1
endif


ifdef PIE
  CFLAGS += -pie -fPIE
  LDFLAGS += -pie -fPIE
  MAKEFLAGS += PIE=1
endif

ifdef NOPIE
  CFLAGS += -no-pie
  LDFLAGS += -no-pie
  MAKEFLAGS += NOPIE=1
  ifdef PIE
    $(error "Could no specify PIE and NOPIE at the same time")
  endif
endif

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: all
all: ${TARGETS_LIBA} ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

virt2phy: virt2phy.o libtest-linux-c.a libtest-linux-numa.a
libtest-linux-mm.a: virt2phy.obj

include ../tlbuild.mk

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.obj: %.c
	@echo -e "  CC OBJ  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*)) -fPIC

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_LIBA): %:
	@echo -e "  AR  \033[1;32m$(^) to $(@)\033[m"
	@ar rcs $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_LIBA)\033[m"
	@rm -f ${TARGETS} *.o *.a *.obj

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=) ${MAKEFLAGS}
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean ${SUB_MAKE_RG}
