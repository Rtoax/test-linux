SHELL = bash

TARGETS :=
TARGETS += server
TARGETS += server-fork-pipe
TARGETS += client

CC = gcc

ALL: $(TARGETS)

server: server.o helpers.o
server-fork-pipe: server-fork-pipe.o
client: client.o helpers.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.txt
