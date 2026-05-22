include ncurses.mk

target-y += getmaxyx
target-y += initscr

LDFLAGS += ${ncurses-ldflags}
