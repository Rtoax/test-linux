target-y += glibc
target-y += clone
target-y += parent_tid
target-y += ns_pid
target-y += ns_net
target-y += container
target-y += uts_hostname
target-y += CLONE_

prep-y := CLONE_.h

CFLAGS := -D__USE_GNU
CFLAGS += -pthread

CFLAGS_ns_pid := -Wno-error=int-to-pointer-cast
CFLAGS_parent_tid := -DPARENT_TID=1
