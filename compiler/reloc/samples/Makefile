
TARGETS := relocation-truncated-to-fit
TARGETS += reloc-types

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
reloc-types: reloc-types.o

CFLAGS_reloc-types := -Wno-error=unused-variable

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@readelf --relocs $(@)
	@readelf --syms $(@)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
