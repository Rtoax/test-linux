# This file be used in test-linux, unuseful in github.com/rtoax/plotcake
include expect.mk
include file.mk
include json-c.mk
include ncurses.mk
include tmux.mk

subdir-y += tools

target-y += plotcake

$(foreach obj, plotcake keyboard file loadavg lgroup line plot ram stdin \
	  ltypes utils axis dialog id-handler scatter, \
  $(eval plotcake-objs += ${obj}.o))

CFLAGS += ${json-c-cflags}

LDFLAGS += -lm
LDFLAGS += ${json-c-ldflags}
LDFLAGS += ${ncurses-ldflags}

prog-y += examples.sh
prog-${HAVE_EXPECT} += examples.exp
prog-${HAVE_TMUX} += examples-tmux.sh
prog-${HAVE_TMUX} += examples-tmux.sh.1

PROG_ARGS_examples-tmux.sh.1 := --vertical-plotting

post-y += build/plotcake
post-y += id-handler
