include ../../../../tlbuild.mk

TARGETS :=
TARGETS += memfd_create
TARGETS += memfd_create-dup2
TARGETS += MFD_ALLOW_SEALING
TARGETS += memfd_secret

CC := gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

memfd_create: memfd_create.o memfd_helpers.o
memfd_create-dup2: memfd_create-dup2.o memfd_helpers.o
MFD_ALLOW_SEALING: MFD_ALLOW_SEALING.o memfd_helpers.o
memfd_secret: memfd_secret.o memfd_helpers.o

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
	${Q}rm -f ${TARGETS} *.o

