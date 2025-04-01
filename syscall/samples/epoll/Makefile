include ../../../tlbuild.mk

TARGETS := eventfd
TARGETS += eventfd-epoll_pwait
TARGETS += level-triggered edge-triggered
TARGETS += tcp-echo

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
# CFLAGS += -DUSE_ONESHOT=1
CFLAGS += -pthread

LDFLAGS := -pthread

CFLAGS_eventfd-epoll_pwait := -DEPOLL_PWAIT=1

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

eventfd: eventfd.o
eventfd-epoll_pwait: eventfd-epoll_pwait.o
level-triggered: level-triggered.o
edge-triggered: edge-triggered.o
tcp-echo: tcp-echo.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt
