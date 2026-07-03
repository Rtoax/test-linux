include json-c.mk
include ncurses.mk

target-y += plotcake

prog-y += examples.sh
prog-y += examples.exp

$(foreach obj, plotcake keyboard file load lgroup line plot ram stdin ltypes \
          utils, \
  $(eval plotcake-objs += ${obj}.o))

CFLAGS += ${json-c-cflags}

LDFLAGS += -lm
LDFLAGS += ${json-c-ldflags}
LDFLAGS += ${ncurses-ldflags}
