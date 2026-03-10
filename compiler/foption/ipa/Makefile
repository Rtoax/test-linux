CC := gcc

include compiler.mk

target-y += fdump-ipa-all fdump-ipa-clones

ifneq ($(CC),clang)
  CFLAGS_fdump-ipa-all := -fdump-ipa-all
  CFLAGS_fdump-ipa-clones := -fdump-ipa-clones
endif

target-clean-y := clean0

include main.mk

clean0:
	${Q}rm -rf fdump-ipa-all.c.* fdump-ipa-clones.c.*
