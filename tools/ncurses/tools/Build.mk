include ncurses.mk

target-y += loadavg
target-y += loadavg.dbg

loadavg.dbg-objs := loadavg.1.o

CFLAGS_loadavg.1 := -DDEBUG=1

LDFLAGS += ${ncurses-ldflags}
