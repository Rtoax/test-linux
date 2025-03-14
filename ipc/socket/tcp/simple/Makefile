include ../../../../tlbuild.mk


TARGETS :=
TARGETS += server
TARGETS += server-fork-pipe
TARGETS += server-pthread
TARGETS += client
TARGETS += client-pthread

CC := gcc

CFLAGS := -O0 -g -ggdb -pthread

ALL: $(TARGETS)

server: server.o helpers.o
server-pthread: server-pthread.o
server-fork-pipe: server-fork-pipe.o
client: client.o helpers.o
client-pthread: client-pthread.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.txt
