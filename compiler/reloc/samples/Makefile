subdir-y :=
ifeq ($(shell uname -m),x86_64)
  subdir-y += x86_64
  subdir-y += i386
endif
ifeq ($(shell uname -m),aarch64)
  subdir-y += aarch64
endif

target-y :=
target-y += relocation-truncated-to-fit
target-y += nostdlib
target-y += reloc-types
target-y += testcase
target-y += testcase-now
target-y += relocs

CFLAGS_reloc-types := -Wno-error=unused-variable
CFLAGS_reloc-types += -Wno-error=unused-function
CFLAGS_reloc-types-libs := ${CFLAGS_reloc-types}
CFLAGS_reloc-types-vars := ${CFLAGS_reloc-types}
CFLAGS_nostdlib-libs := $(CFLAGS_nostdlib)
CFLAGS_testcase := -Wl,-z,relro
CFLAGS_testcase-now := -Wl,-z,relro,-z,now

LDFLAGS_nostdlib := -nostdlib

target-prep-y := relocs-gen.h

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
