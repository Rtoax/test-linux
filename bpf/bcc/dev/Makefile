BCC_SYMS_HDR := /usr/include/bcc/bcc_syms.h

target-y := symcache
target-y += bcc_elf_is_shared_obj

LDFLAGS := -lbcc

ifeq ($(wildcard $(BCC_SYMS_HDR)),)
  target-y :=
  $(warning "WARNING: You need to install bcc dev headers")
endif

include ../../../template/main.mk

symcache: symcache.o
bcc_elf_is_shared_obj: bcc_elf_is_shared_obj.o
