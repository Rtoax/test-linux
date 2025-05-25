include ../../../../tlbuild.mk

TARGETS := main
TARGETS += main-pie

CC := gcc

CFLAGS :=
LDFLAGS :=

# FIXME: PIE not implement, because _start address in lds
CFLAGS += -Wl,-Tld-insert-text.lds,-Tld-insert-data.lds
CFLAGS += -Wl,--no-warn-rwx-segments

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

main.o: init.h log.h
main: main.o
main-pie.o: init.h log.h
main-pie: main-pie.o

CFLAGS_main += -no-pie
LDFLAGS_main += -no-pie
CFLAGS_main-pie := -fpie
LDFLAGS_main-pie := -pie

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o

