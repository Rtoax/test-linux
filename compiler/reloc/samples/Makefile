sub-dir :=
ifeq ($(shell uname -m),x86_64)
  sub-dir += x86_64
  sub-dir += i386
endif
ifeq ($(shell uname -m),aarch64)
  sub-dir += aarch64
endif

targets :=
targets += relocation-truncated-to-fit
targets += nostdlib
targets += reloc-types
targets += testcase
targets += testcase-now
targets += relocs

CFLAGS_reloc-types := -Wno-error=unused-variable
CFLAGS_reloc-types += -Wno-error=unused-function
CFLAGS_reloc-types-libs := ${CFLAGS_reloc-types}
CFLAGS_reloc-types-vars := ${CFLAGS_reloc-types}
CFLAGS_nostdlib-libs := $(CFLAGS_nostdlib)
CFLAGS_testcase := -Wl,-z,relro
CFLAGS_testcase-now := -Wl,-z,relro,-z,now

LDFLAGS_nostdlib := -nostdlib

targets-prep := relocs-gen.h

include ../../../template/main.mk

relocs-gen.h:
	$(call log_tgt_exe,HDR,,$(@))
	${Q}./relocs.h.sh

relocs: relocs.o
relocation-truncated-to-fit: relocation-truncated-to-fit.o relocation-truncated-to-fit-obj.o
reloc-types: reloc-types.o reloc-types-libs.o reloc-types-vars.o
nostdlib: nostdlib.o nostdlib-libs.o
testcase: testcase.o
testcase-now: testcase-now.o

# TODO: use it
define print_elf
	@echo -e "# $(1)" > ${1}.readelf.log
	@readelf --relocs --syms --wide $(1) >> ${1}.readelf.log
endef
