include ../../tlbuild.mk

TARGETS := oom
TARGETS += popen

CC := gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

CFLAGS_popen = -DPOPEN=1

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

oom.o: oom_helpers.h
popen.o: oom_helpers.h
oom_helpers.o: oom_helpers.h

oom: oom.o oom_helpers.o
popen: popen.o oom_helpers.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
