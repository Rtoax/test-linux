include ../../tlbuild.mk


TARGETS :=

CC := gcc

TARGETS += hello


CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -specs=$(shell pwd)/definitions
CFLAGS += -specs=$(shell pwd)/definitions2

LDFLAGS :=

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*)) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	@gcc $(CFLAGS) -dumpspecs

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.s
