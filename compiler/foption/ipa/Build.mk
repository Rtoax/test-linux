include compiler.mk

target-y += fdump-ipa-all fdump-ipa-clones
target-clean-y := clean0

ifneq ($(CC),clang)
  CFLAGS_fdump-ipa-all := -fdump-ipa-all
  CFLAGS_fdump-ipa-clones := -fdump-ipa-clones
endif
