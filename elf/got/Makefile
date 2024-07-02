
TARGETS :=
TARGETS += _GLOBAL_OFFSET_TABLE_

CFLAGS :=
LDFLAGS :=
LDLIBS :=

ifdef PIC
# FIXME: Why cause 'Illegal instruction (core dumped)' on x86
CFLAGS__GLOBAL_OFFSET_TABLE_ := -fpic
endif

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
_GLOBAL_OFFSET_TABLE_: _GLOBAL_OFFSET_TABLE_.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.s *.o *.d
