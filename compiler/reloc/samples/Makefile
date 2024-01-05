
TARGETS := relocation-truncated-to-fit
TARGETS += nostdlib
TARGETS += reloc-types
TARGETS += testcase
TARGETS += testcase-now

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -O0

ifdef DEBUG
CFLAGS += -g -ggdb
endif

build: ${TARGETS}
	@echo
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
	@echo -e "\033[1;33m------------- $(1) ------------\033[m"
	@readelf --relocs $(1)
	@readelf --syms $(1)
endef

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(call print_elf,$(@))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS)
	$(call print_elf,$(@))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
