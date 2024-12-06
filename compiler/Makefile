# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


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

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

TARGETS :=
TARGETS += __GNUC__
TARGETS += __VERSION__

CC := gcc

include compiler.mk

.PHONY: build
build: $(TARGETS) $(sub-dir-build)
	@echo -e "CC(${CC}) VERSION ${CC_VERSION} = ${CC_MAJOR}.${CC_MINOR} (${CC_FULLVERSION})"
	@echo -e " \033[1;33m Done \033[m"

__VERSION__: __VERSION__.o
__GNUC__: __GNUC__.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -rf $(TARGETS) *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
