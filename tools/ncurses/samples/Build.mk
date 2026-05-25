include ncurses.mk

target-y += getch
target-y += getmaxyx
target-y += initscr

LDFLAGS += ${ncurses-ldflags}
