include ../../tlbuild.mk


TARGETS :=
TARGETS += nostartfiles

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS_nostartfiles := -nostartfiles
# /usr/bin/ld: warning: cannot find entry symbol _start; defaulting to 0000000000401000
LDFLAGS_nostartfiles += -lc --entry whatever

build: ${TARGETS}
	@echo -e "  CC = ${CC}"
	@echo -e "  CFLAGS = ${CFLAGS}"
	@echo -e " \033[1;33m Done \033[m"

nostartfiles: nostartfiles.o

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
	${Q}rm -f ${TARGETS} *.o
