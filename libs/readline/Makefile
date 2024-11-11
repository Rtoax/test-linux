SHELL = bash

READLINE_HDR = /usr/include/readline/readline.h

TARGETS :=
TARGETS += rlversion
TARGETS += rltest

ifeq ($(wildcard $(READLINE_HDR)),)
  $(warning "WARNING: Must install readline development header")
  TARGETS :=
endif

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

ifneq ($(wildcard $(READLINE_HDR)),)
  CFLAGS += -lreadline -lutil -ltermcap -lhistory
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
rlversion: rlversion.o
rltest: rltest.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d
