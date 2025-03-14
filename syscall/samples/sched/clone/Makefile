include ../../../../tlbuild.mk

TARGETS :=
TARGETS += glibc
TARGETS += clone
TARGETS += parent_tid
TARGETS += ns_pid
TARGETS += ns_net
TARGETS += container
TARGETS += uts_hostname
TARGETS += CLONE_

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE -D__USE_GNU
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

ifdef STATIC
  CFLAGS += -static
endif

CFLAGS_ns_pid := -Wno-error=int-to-pointer-cast
CFLAGS_parent_tid := -DPARENT_TID=1

build: CLONE_.h ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

CLONE_.h:
	${Q}./CLONE_.sh

glibc: glibc.o
clone: clone.o
parent_tid: parent_tid.o
ns_pid: ns_pid.o
ns_net: ns_net.o
container: container.o
uts_hostname: uts_hostname.o
CLONE_: CLONE_.o CLONE_.h

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d CLONE_.h

