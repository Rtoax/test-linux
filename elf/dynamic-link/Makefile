SHELL = bash

TARGETS := main

TARGETS_SO := libfoo.so

CC := gcc

CFLAGS :=
LDFLAGS :=

CFLAGS_main := -lfoo
LDFLAGS_main := libfoo.so

.PHONY: build
build: ${TARGETS_SO} ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
main: main.o
libfoo.so: foo.oso

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.oso: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*)) -fPIC

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

$(TARGETS_SO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) -shared -fPIC $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) ./main

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_SO)\033[m"
	@rm -f ${TARGETS} ${TARGETS_SO} *.o *.oso
