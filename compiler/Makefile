# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
include ../scripts/logos.mk

sub-dir := annobin
sub-dir += ast
sub-dir += linker
sub-dir += llvm
sub-dir += __atomic
sub-dir += __attribute__
sub-dir += __builtin_
sub-dir += dwarf
sub-dir += foption option
sub-dir += machine-option
sub-dir += openmp
sub-dir += optimize
sub-dir += pragma
sub-dir += reloc
sub-dir += specs
sub-dir += __sync
sub-dir += Wwarn

include ../template/subdir-header.mk

TARGETS :=
TARGETS += __GNUC__
TARGETS += __GNUC_PREREQ
TARGETS += __VERSION__

CC := gcc

include compiler.mk

.PHONY: build
build: $(CC)-macros.h $(TARGETS) $(sub-dir-build)
	@echo -e "CC(${CC}) VERSION ${CC_VERSION} = ${CC_MAJOR}.${CC_MINOR} (${CC_FULLVERSION})"
	@echo -e " \033[1;33m Done \033[m"
	@$(call tl_ascii_logo_gnu)

$(CC)-macros.h:
	@echo -e "  GEN  \033[1m$(@)\033[m"
	$(call gen_compiler_macro_hdr,$(@))

__VERSION__: __VERSION__.o
__GNUC__: __GNUC__.o
__GNUC_PREREQ: __GNUC_PREREQ.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -rf $(TARGETS) *.o *-macros.h

include ../template/subdir-footer.mk
