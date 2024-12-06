SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


LDS_INSERT := ld-insert.lds

TARGETS := main
TARGETS += main-pie

CC := gcc

CFLAGS :=
LDFLAGS :=

# FIXME: PIE not implement, because _start address in lds
CFLAGS += -Wl,-T${LDS_INSERT}
CFLAGS += -Wl,--no-warn-rwx-segments

.PHONY: build
build: ${TARGETS} ${LDS_INSERT}
	@echo -e " \033[1;33m Done \033[m"

main: main.o
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

