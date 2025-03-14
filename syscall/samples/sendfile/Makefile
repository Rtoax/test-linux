include ../../../tlbuild.mk


TARGETS :=
TARGETS += sendfile
TARGETS += sendfile-tcp-server
TARGETS += sendfile-socket

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -pthread

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

sendfile: sendfile.o
sendfile-tcp-server: sendfile-tcp-server.o
sendfile-socket: sendfile-socket.o

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
	${Q}rm -rf ${TARGETS} *.o os-release
