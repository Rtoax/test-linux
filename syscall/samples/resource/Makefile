include ../../../tlbuild.mk


TARGETS :=
TARGETS += getrlimit setrlimit ulimit prlimit
TARGETS += fork-inherit
TARGETS += getrusage vlimit

CC := gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

getrlimit: getrlimit.o resource_helpers.o
setrlimit: setrlimit.o resource_helpers.o
prlimit: prlimit.o resource_helpers.o
ulimit: ulimit.o
fork-inherit: fork-inherit.o resource_helpers.o
getrusage: getrusage.o resource_helpers.o
vlimit: vlimit.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -rf ${TARGETS} *.o

