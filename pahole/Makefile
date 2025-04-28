# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
include pahole.mk

sub-dir :=

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

test: $(sub-dir-test)

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN"

include ../template/subdir-footer.mk
