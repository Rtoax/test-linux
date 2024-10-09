SHELL = bash

CC = gcc
LD = ld
NASM = $(shell which nasm 2>/dev/null)

TARGETS_AS :=

ifeq ($(shell uname -m),x86_64)
  ifneq ($(NASM),)
    TARGETS_AS += hello-as
  endif
endif

all: ${TARGETS_AS}

hello-as: hello-as.o

%.o: %.asm
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(NASM) $(<) -felf64 -o $(@) $(CFLAGS) $(CFLAGS_$(*))

${TARGETS_AS}: %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(LD) -T $(@).ld -o $(@) $(LDFLAGS) $(LDFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS_AS)\033[m"
	@rm -f ${TARGETS_AS} *.o
