include json-c.mk
include ncurses.mk

target-y += plotcake

prog-y += examples.sh
prog-y += examples.exp

$(foreach obj, plotcake keyboard file load value plot ram stdin lines, \
  $(eval plotcake-objs += ${obj}.o))

CFLAGS += ${json-c-cflags}

LDFLAGS += -lm
LDFLAGS += ${json-c-ldflags}
LDFLAGS += ${ncurses-ldflags}
