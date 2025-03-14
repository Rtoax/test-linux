include ../../../tlbuild.mk



TARGETS := unix-server
TARGETS += unix-client
TARGETS += unix-client-memfd_create
TARGETS += socketpair

DEBUG := yes
CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wno-error=unused-function

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
unix-server: unix-server.o common.o
unix-client: unix-client.o common.o
unix-client-memfd_create: unix-client-memfd_create.o common.o
socketpair: socketpair.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
