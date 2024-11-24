# SPDX-License-Identifier: GPL-3.0
SHELL = bash

sub-dir := samples

TARGETS :=
TARGETS += numa_mem

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: numa_mem.h ${TARGETS} $(sub-dir-build)
	@./info.sh raw
	@./info.sh pure
	@./info.sh c
	@echo -e " \033[1;33m Done \033[m"

numa_mem.h:
	@./info.sh c

numa_mem: numa_mem.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e " CLEAN \033[1;33m ${TARGETS} ${sub-dir} \033[m"
	@rm -f numa_mem.h ${TARGETS} *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
