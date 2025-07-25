BCC_SYMS_HDR := /usr/include/bcc/bcc_syms.h

targets := symcache
targets += bcc_elf_is_shared_obj

LDFLAGS := -lbcc

ifeq ($(wildcard $(BCC_SYMS_HDR)),)
  targets :=
  $(warning "WARNING: You need to install bcc dev headers")
endif

include ../../../template/main.mk

symcache: symcache.o
bcc_elf_is_shared_obj: bcc_elf_is_shared_obj.o
