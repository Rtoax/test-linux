SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

TARGETS :=
TARGETS += cgroup_event_listener

DEBUG = yes
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

cgroup_event_listener: cgroup_event_listener.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^)

test: ${TARGETS}
	@echo empty >/dev/null

clean:
	@echo -e "  RM  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
