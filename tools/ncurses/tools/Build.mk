include ncurses.mk

target-y += plotcake
target-y += plotcake.dbg

prog-y += examples.sh

plotcake-objs := load.o value.o plot.o ram.o stdin.o lines.o
plotcake.dbg-objs := plotcake.1.o load.1.o value.1.o plot.1.o ram.1.o stdin.1.o lines.1.o

$(foreach obj, plotcake load value plot ram stdin lines, \
  $(eval CFLAGS_${obj}.1 := -DDEBUG=1))

LDFLAGS += -lm
LDFLAGS += ${ncurses-ldflags}
