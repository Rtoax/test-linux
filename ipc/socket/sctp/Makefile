TARGETS :=
TARGETS += IPPROTO_SCTP
TARGETS += client server

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lsctp

LDFLAGS := $(CFLAGS)

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
IPPROTO_SCTP: IPPROTO_SCTP.o
client: client.o
server: server.o

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
