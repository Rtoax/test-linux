include ../../../tlbuild.mk

CC := gcc

include ../../compiler.mk

TARGETS :=
TARGETS += ffat-lto-objects
TARGETS += flto

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

CFLAGS_ffat-lto-objects := -flto -ffat-lto-objects
CFLAGS_flto := -flto=auto
LDFLAGS_flto := -flto=auto

.PHONY: build
build: ${TARGETS}
	@echo -e "  CC = ${CC}"
	@echo -e "  CFLAGS = ${CFLAGS}"
	@echo -e " \033[1;33m Done \033[m"

ffat-lto-objects: ffat-lto-objects.o
flto: flto.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=-nof.s) $(CFLAGS) -Wno-error

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.s

