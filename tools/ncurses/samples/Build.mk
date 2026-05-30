include ncurses.mk

target-y += getch
target-y += getmaxyx
target-y += keyname
target-y += initscr
target-y += setlocale

LDFLAGS += ${ncurses-ldflags}
