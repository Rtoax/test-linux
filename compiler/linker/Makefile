# SPDX-License-Identifier: GPL-3.0
LD_LLD := $(shell which lld 2>/dev/null)
LD_MOLD := $(shell which mold 2>/dev/null)

sub-dir := linker-script
sub-dir += LD_PRELOAD

targets-shell := LD_SHOW_AUXV.sh

targets := pushsection
targets += attribute
targets += bfd
targets += gold
ifneq ($(wildcard $(LD_LLD)),)
  targets += lld
else
  $(warning "WARNING: not found mold lld")
endif
ifneq ($(wildcard $(LD_MOLD)),)
  targets += mold
else
  $(warning "WARNING: not found mold linker")
endif

CC := gcc
LD := ld

# Use the bfd linker instead of the default linker.
LDFLAGS_bfd := -fuse-ld=bfd
# Use the gold linker instead of the default linker.
LDFLAGS_gold := -fuse-ld=gold
# Use the LLVM lld linker instead of the default linker.
LDFLAGS_lld := -fuse-ld=lld
# Use the Modern Linker (mold) instead of the default linker.
LDFLAGS_mold := -fuse-ld=mold
LDFLAGS_pushsection := -nostdlib
LDFLAGS_attribute := -nostdlib

include ../../template/main.mk

pushsection: pushsection.o
attribute: attribute.o
bfd: bfd.o
gold: gold.o
lld: lld.o
mold: mold.o
