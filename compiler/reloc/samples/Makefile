SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


sub-dir :=
ifeq ($(shell uname -m),x86_64)
  sub-dir += x86_64
  sub-dir += i386
endif
ifeq ($(shell uname -m),aarch64)
  sub-dir += aarch64
endif

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

TARGETS :=
TARGETS += relocation-truncated-to-fit
TARGETS += nostdlib
TARGETS += reloc-types
TARGETS += testcase
TARGETS += testcase-now

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -O0

ifdef PIC
  CFLAGS += -fpic
endif
ifdef DEBUG
  CFLAGS += -g -ggdb
endif

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
relocation-truncated-to-fit: relocation-truncated-to-fit.o relocation-truncated-to-fit-obj.o
reloc-types: reloc-types.o reloc-types-libs.o reloc-types-vars.o
nostdlib: nostdlib.o nostdlib-libs.o
testcase: testcase.o
testcase-now: testcase-now.o

CFLAGS_reloc-types := -Wno-error=unused-variable
CFLAGS_reloc-types += -Wno-error=unused-function
CFLAGS_reloc-types-libs := ${CFLAGS_reloc-types}
CFLAGS_reloc-types-vars := ${CFLAGS_reloc-types}
CFLAGS_nostdlib := -nostdlib
CFLAGS_nostdlib-libs := $(CFLAGS_nostdlib)
CFLAGS_testcase := -Wl,-z,relro
CFLAGS_testcase-now := -Wl,-z,relro,-z,now

define print_elf
	@echo -e "# $(1)" > ${1}.readelf.log
	@readelf --relocs --syms --wide $(1) >> ${1}.readelf.log
endef

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	$(call print_elf,$(@))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(CFLAGS) $(CFLAGS_$(*))
	$(call print_elf,$(@))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.readelf.log

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=) CC=$(CC) CXX=$(CXX)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
