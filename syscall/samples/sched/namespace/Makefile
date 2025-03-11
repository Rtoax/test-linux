include ../../../../tlbuild.mk

TARGETS :=
TARGETS += dummy dummy-fork dummy-vfork
TARGETS += setns
TARGETS += unshare unshare-execve

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE -D__USE_GNU
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

CFLAGS_dummy := -static
CFLAGS_dummy-fork := -static -DTRY_FORK=1
CFLAGS_dummy-vfork := -static -DTRY_VFORK=1

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

dummy: dummy.o
dummy-fork: dummy-fork.o
dummy-vfork: dummy-vfork.o
setns: setns.o
unshare: unshare.o
unshare-execve: unshare-execve.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d

