CC := gcc

include ../../compiler.mk

TARGETS :=
TARGETS += fdump-ipa-all fdump-ipa-clones

ifneq ($(CC),clang)
  CFLAGS_fdump-ipa-all := -fdump-ipa-all
  CFLAGS_fdump-ipa-clones := -fdump-ipa-clones
endif

TARGETS_CLEAN := clean0

include ../../../template/main.mk

fdump-ipa-all: fdump-ipa-all.o
fdump-ipa-clones: fdump-ipa-clones.o

clean0:
	${Q}rm -rf fdump-ipa-all.c.* fdump-ipa-clones.c.*
