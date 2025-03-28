include ../../../../tlbuild.mk

TARGETS :=
TARGETS += dummy dummy-fork dummy-vfork dummy-popen
TARGETS += setns
TARGETS += unshare unshare-execve

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE -D__USE_GNU
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

CFLAGS_dummy := -static
CFLAGS_dummy-fork := -static -DTRY_FORK=1
CFLAGS_dummy-vfork := -static -DTRY_VFORK=1
CFLAGS_dummy-popen := -static -DTRY_POPEN=1

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

helpers_fork.o: helpers_fork.h

dummy: dummy.o
dummy-fork: dummy-fork.o helpers_fork.o
dummy-vfork: dummy-vfork.o helpers_fork.o
dummy-popen: dummy-popen.o helpers_fork.o
setns: setns.o
unshare: unshare.o
unshare-execve: unshare-execve.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	${Q}timeout --signal=SIGINT 4 ./fork-ENOMEM.sh test3 || true

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d

