# This file be used in test-linux, unuseful in github.com/rtoax/plotcake
include expect.mk
include file.mk
include json-c.mk
include ncurses.mk
include tmux.mk

target-y += plotcake

prog-y += examples.sh
prog-${HAVE_EXPECT} += examples.exp
prog-${HAVE_TMUX} += examples-tmux.sh

$(foreach obj, plotcake keyboard file loadavg lgroup line plot ram stdin \
	  ltypes utils axis dialog fd-handler, \
  $(eval plotcake-objs += ${obj}.o))

CFLAGS += ${json-c-cflags}

LDFLAGS += -lm
LDFLAGS += ${json-c-ldflags}
LDFLAGS += ${ncurses-ldflags}

post-y := build/plotcake
