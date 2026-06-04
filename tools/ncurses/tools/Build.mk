include ncurses.mk

target-y += plotcake
target-y += plotcake.dbg

prog-y += examples.sh

plotcake-objs :=
plotcake.dbg-objs := plotcake.1.o

$(foreach obj, plotcake keyboard file load value plot ram stdin lines, \
  $(eval plotcake-objs += ${obj}.o) \
  $(eval plotcake.dbg-objs += ${obj}.1.o) \
  $(eval CFLAGS_${obj}.1 := -DDEBUG=1))

LDFLAGS += -lm
LDFLAGS += ${ncurses-ldflags}
