# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk


sub-dir := make
sub-dir += glibc
sub-dir += gnupg

TARGETS := __GNUC__

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) ${TARGETS}

__GNUC__: __GNUC__.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -rf ${TARGETS} *.o

include ../template/subdir-footer.mk
