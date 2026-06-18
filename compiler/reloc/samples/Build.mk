subdir-${IS_X86_64} += x86_64
subdir-${IS_X86_64} += i386
subdir-${IS_AARCH64} += aarch64

target-y += relocation-truncated-to-fit
target-y += nostdlib
target-y += reloc-types
target-y += testcase
target-y += testcase-now
target-y += relocs

relocation-truncated-to-fit-objs := relocation-truncated-to-fit-obj.o
reloc-types-objs := reloc-types-libs.o reloc-types-vars.o
nostdlib-objs := nostdlib-libs.o

CFLAGS_reloc-types := -Wno-error=unused-variable
CFLAGS_reloc-types += -Wno-error=unused-function
CFLAGS_reloc-types-libs := ${CFLAGS_reloc-types}
CFLAGS_reloc-types-vars := ${CFLAGS_reloc-types}
CFLAGS_nostdlib-libs := $(CFLAGS_nostdlib)
CFLAGS_testcase := -Wl,-z,relro
CFLAGS_testcase-now := -Wl,-z,relro,-z,now

LDFLAGS_nostdlib := -nostdlib

prep-y := relocs-gen.h

# TODO: use it
define print_elf
	@echo -e "# $(1)" > ${1}.readelf.log
	@readelf --relocs --syms --wide $(1) >> ${1}.readelf.log
endef
