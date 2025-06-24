include ../../tlbuild.mk


TARGETS :=
TARGETS += arg arg-O3

LDFLAGS :=

CFLAGS :=

ifdef DEBUG
  CFLAGS += -DDEBUG -g -ggdb
endif

CFLAGS_arg := -O0
CFLAGS_arg-O3 := -O3

build: ${TARGETS}
	@${SHELL} ./optimizers.sh
	@echo -e " \033[1;33m Done \033[m"

arg: arg.o
arg-O3: arg-O3.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.log
