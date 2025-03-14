# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

LD_LLD := $(shell which lld 2>/dev/null)
LD_MOLD := $(shell which mold 2>/dev/null)

sub-dir := linker-script
sub-dir += LD_PRELOAD

TARGETS :=
TARGETS += pushsection
TARGETS += attribute
TARGETS += bfd
TARGETS += gold
ifneq ($(wildcard $(LD_LLD)),)
  TARGETS += lld
else
  $(warning "WARNING: not found mold lld")
endif
ifneq ($(wildcard $(LD_MOLD)),)
  TARGETS += mold
else
  $(warning "WARNING: not found mold linker")
endif

CC = gcc
LD = ld

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=

# Use the bfd linker instead of the default linker.
LDFLAGS_bfd := -fuse-ld=bfd
# Use the gold linker instead of the default linker.
LDFLAGS_gold := -fuse-ld=gold
# Use the LLVM lld linker instead of the default linker.
LDFLAGS_lld := -fuse-ld=lld
# Use the Modern Linker (mold) instead of the default linker.
LDFLAGS_mold := -fuse-ld=mold
CFLAGS_pushsection := -nostdlib
CFLAGS_attribute := -nostdlib

include ../../template/subdir-header.mk

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

pushsection: pushsection.o
attribute: attribute.o
bfd: bfd.o
gold: gold.o
lld: lld.o
mold: mold.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*)) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.s

include ../../template/subdir-footer.mk
