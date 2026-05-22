include ncurses.mk

target-y += loadavg

LDFLAGS += ${ncurses-ldflags}
