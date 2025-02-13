SHELL = bash
include ../../../tlbuild.mk


LKSCTP_TOOLS_DEVEL=/usr/include/netinet/sctp.h

TARGETS :=
ifneq ($(wildcard $(LKSCTP_TOOLS_DEVEL)),)
TARGETS += IPPROTO_SCTP
TARGETS += client server
else
$(warning "WARNING: Maybe install lksctp-tools development package")
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lsctp

LDFLAGS := $(CFLAGS)

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
IPPROTO_SCTP: IPPROTO_SCTP.o
client: client.o
server: server.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
