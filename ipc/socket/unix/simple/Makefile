include ../../../../tlbuild.mk


CC := gcc

TARGETS :=
TARGETS += tcp-server tcp-client tcp-server-noclose
TARGETS += udp-server udp-client

ALL: $(TARGETS)

tcp-server: tcp-server.o
tcp-server-noclose: tcp-server-noclose.o
tcp-client: tcp-client.o
udp-server: udp-server.o
udp-client: udp-client.o

CFLAGS_tcp-server-noclose := -DNO_CLOSE_CLIENT_FD=1

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o *.sock

