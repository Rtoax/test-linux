# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
include numactl.mk

sub-dir := samples

TARGETS :=
TARGETS_LIBA :=

TARGETS += numa_mem

TARGETS_LIBA += libtest-linux-numa.a

CFLAGS :=
CFLAGS += -g
CFLAGS += -lnuma

CFLAGS_numa_mem := -DTEST_MAIN=1

include ../template/subdir-header.mk

.PHONY: build
build: numa_mem.h ${TARGETS_LIBA} ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

numa_mem.h:
	${Q}./info.sh c

numa_mem: numa_mem.o
libtest-linux-numa.a: numa_mem.h numa_mem.a.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

include ../template/target-liba.mk

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e " CLEAN \033[1;33m ${TARGETS} ${sub-dir} ${TARGETS_LIBA} \033[m"
	${Q}rm -f numa_mem.h ${TARGETS} ${TARGETS_LIBA} *.o

include ../template/subdir-footer.mk
