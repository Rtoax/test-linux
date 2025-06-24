include ../../../tlbuild.mk

CC := gcc

include ../../compiler.mk

TARGETS :=
# Default
TARGETS += fzero-initialized-in-bss
TARGETS += fno-zero-initialized-in-bss

CFLAGS :=
CFLAGS += -Wno-error=unused-variable

CFLAGS_fzero-initialized-in-bss := -fzero-initialized-in-bss
CFLAGS_fno-zero-initialized-in-bss := -fno-zero-initialized-in-bss

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

fzero-initialized-in-bss: fzero-initialized-in-bss.o
fno-zero-initialized-in-bss: fno-zero-initialized-in-bss.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.s

