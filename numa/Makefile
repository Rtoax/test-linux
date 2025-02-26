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

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

.PHONY: build
build: numa_mem.h ${TARGETS_LIBA} ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

numa_mem.h:
	@./info.sh c

numa_mem: numa_mem.o
libtest-linux-numa.a: numa_mem.h numa_mem.obj

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.obj: %.c
	@echo -e "  CC OBJ  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*)) -fPIC

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_LIBA): %:
	@echo -e "  AR  \033[1;32m$(^) to $(@)\033[m"
	@ar rcs $(@) $(^)

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e " CLEAN \033[1;33m ${TARGETS} ${sub-dir} ${TARGETS_LIBA} \033[m"
	${Q}rm -f numa_mem.h ${TARGETS} ${TARGETS_LIBA} *.o *.obj

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
