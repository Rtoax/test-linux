targets :=
targets += glibc
targets += clone
targets += parent_tid
targets += ns_pid
targets += ns_net
targets += container
targets += uts_hostname
targets += CLONE_

CFLAGS := -D__USE_GNU
CFLAGS += -pthread

ifdef STATIC
  CFLAGS += -static
endif

CFLAGS_ns_pid := -Wno-error=int-to-pointer-cast
CFLAGS_parent_tid := -DPARENT_TID=1

targets-prep := CLONE_.h

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

