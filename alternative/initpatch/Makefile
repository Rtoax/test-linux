SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


LDS := ld-alternative.lds

TARGETS :=

ifeq ($(shell uname -m),x86_64)
  TARGETS += main
else
  $(warning Not support arch except x86_64)
endif

CC := gcc

CFLAGS :=
LDFLAGS :=

CFLAGS += -Wl,-T${LDS}
ifneq ($(shell ld --help | grep -o no-warn-rwx-segments),)
  CFLAGS += -Wl,--no-warn-rwx-segments
endif

.PHONY: build
build: ${TARGETS} ${LDS}
	@echo -e " \033[1;33m Done \033[m"

main: main.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

