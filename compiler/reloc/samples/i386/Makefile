SHELL = bash

TARGETS :=
TARGETS_O :=
TARGETS_SO :=
TARGETS_A :=
TARGETS_S_O :=

CC := gcc
AS := as

CFLAGS :=
LDFLAGS :=
CFLAGS_PIE :=
LDFLAGS_PIE :=

TARGETS += R_386_32

CFLAGS += -m32
LDFLAGS += -m32

# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
ifdef PIE
  CFLAGS_PIE += -fpie
  LDFLAGS_PIE += -pie
else
  CFLAGS_PIE += -no-pie
  LDFLAGS_PIE += -no-pie
endif

ifdef VERBOSE
  CFLAGS += -Q
  LDFLAGS += -Q
endif

define print_elf_reloc
	@echo -e "# $(1)" > ${1}.reloc
	@readelf --relocs --wide $(1) >> ${1}.reloc
endef

.PHONY: build
build: ${TARGETS_SO} ${TARGETS_A} ${TARGETS} ${TARGETS_O} ${TARGETS_S_O}
	@echo -e " \033[1;33m Done \033[m"

R_386_32: R_386_32.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_PIE) $(CFLAGS_$(*))
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -S $(<) -o $(<:.c=.c.s) $(CFLAGS) $(CFLAGS_PIE) $(CFLAGS_$(*))
	@$(call print_elf_reloc,$(@))

%.So: %.S
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@${AS} --32 -o $(@) $(<)
	@$(call print_elf_reloc,$(@))

%.obj: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*)) -fPIC

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_PIE) $(LDFLAGS_$(*))
	@$(call print_elf_reloc,$(@))

$(TARGETS_SO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) -shared -fPIC $(LDFLAGS) $(LDFLAGS_$(*))

$(TARGETS_A): %:
	@echo -e "  AR  \033[1;32m$(^) to $(@)\033[m"
	@ar rcs $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_SO) $(TARGETS_A) ${TARGETS_O} ${TARGETS_S_O}\033[m"
	@rm -f ${TARGETS} ${TARGETS_SO} ${TARGETS_A} ${TARGETS_O} ${TARGETS_S_O} \
		*.o *.obj *.reloc *.So *.c.s
