include ../../tlbuild.mk

TARGETS :=
TARGETS += test

DEBUG :=
CC := gcc

CFLAGS :=

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

CFLAGS += -funwind-tables

build: ${TARGETS} ${TARGETS_CPP}
	@echo -e " \033[1;33m Done \033[m"

test: test.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

${TARGETS}: %:
	@echo -e "  LD  \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(<)
	@echo -e "  \033[1;32m---- show .eh_frame ----\033[m"
	@readelf -wF $(@)
	@echo -e "  \033[1;32m---- show raw .eh_frame ----\033[m"
	@readelf -wf $(@)

clean:
	@echo -e "  CLEAN  \033[1m$(TARGETS) ${TARGETS_CPP}\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_CPP} *.o
