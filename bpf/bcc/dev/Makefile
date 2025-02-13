SHELL = bash
include ../../../tlbuild.mk


BCC_SYMS_HDR := /usr/include/bcc/bcc_syms.h

CC = gcc

TARGETS := symcache
TARGETS += bcc_elf_is_shared_obj

CFLAGS := -lbcc
LDFLAGS := -lbcc

ifeq ($(wildcard $(BCC_SYMS_HDR)),)
  TARGETS :=
  $(warning "WARNING: You need to install bcc dev headers")
endif

ifdef PIE
  CFLAGS += -pie -fPIE
  LDFLAGS += -pie -fPIE
endif

ifdef NOPIE
  CFLAGS += -no-pie
  LDFLAGS += -no-pie
  ifdef PIE
    $(error "Could no specify PIE and NOPIE at the same time")
  endif
endif

all: $(TARGETS)

symcache: symcache.o
bcc_elf_is_shared_obj: bcc_elf_is_shared_obj.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

