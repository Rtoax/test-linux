TARGETS :=
TARGETS += glibc
TARGETS += clone
TARGETS += parent_tid
TARGETS += ns_pid
TARGETS += ns_net
TARGETS += container
TARGETS += uts_hostname
TARGETS += CLONE_

CFLAGS := -D__USE_GNU
CFLAGS += -pthread

ifdef STATIC
  CFLAGS += -static
endif

CFLAGS_ns_pid := -Wno-error=int-to-pointer-cast
CFLAGS_parent_tid := -DPARENT_TID=1

TARGETS_PREP := CLONE_.h

include ../../../../template/main.mk

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

