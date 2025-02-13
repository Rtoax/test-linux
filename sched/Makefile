include ../tlbuild.mk


TARGETS :=
TARGETS += current
TARGETS += uninterruptible
TARGETS += hung
TARGETS += zombie
TARGETS += stopped

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

current: current.o
uninterruptible: uninterruptible.o
hung: hung.o
zombie: zombie.o
stopped: stopped.o

kill-uninterruptible:
	kill $(shell pgrep uninterruptible)

kill-zombie:
	kill $(shell pgrep zombie)

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
