include ncurses.mk

target-y += loadavg
target-y += loadavg.dbg

loadavg-objs := value.o plot.o ram.o
loadavg.dbg-objs := loadavg.1.o value.o plot.o ram.o

CFLAGS_loadavg.1 := -DDEBUG=1

LDFLAGS += ${ncurses-ldflags}
