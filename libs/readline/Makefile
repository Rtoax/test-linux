READLINE_HDR = /usr/include/readline/readline.h

TARGETS :=
ifneq ($(wildcard $(READLINE_HDR)),)
TARGETS += rlversion
TARGETS += rltest
else
$(error "ERROR: Must install libaio development header")
endif

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

ifneq ($(wildcard $(READLINE_HDR)),)
CFLAGS += -lreadline -lutil -ltermcap -lhistory
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
rlversion: rlversion.o
rltest: rltest.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
