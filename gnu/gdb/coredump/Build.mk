target-y := coredump

LDFLAGS += -pthread

prog-y := prlimit.sh
prog-y += list.sh
prog-y += info.sh
