# This file be used in test-linux, unuseful in github.com/rtoax/plotcake
include expect.mk
include file.mk
include json-c.mk
include ncurses.mk
include tmux.mk

subdir-y += tools

target-y += plotcake
target-y += id-handler-exec

$(foreach obj, plotcake keyboard file loadavg lgroup line plot ram stdin \
	  draw utils axis dialog id-handler scatter color log value \
	  stdin-scatter legend, \
  $(eval plotcake-objs += ${obj}.o))

id-handler-exec-objs := id-handler.1.o

CFLAGS += ${json-c-cflags}
CFLAGS_id-handler.1 := -DTEST_MAIN

LDFLAGS += -lm
LDFLAGS += ${json-c-ldflags}
LDFLAGS += ${ncurses-ldflags}

SFX_MAX_N := 20

prog-y += id-handler-exec
prog-y += examples.sh
prog-${HAVE_EXPECT} += examples.exp
prog-${HAVE_TMUX} += examples-tmux.sh
prog-${HAVE_TMUX} += examples-tmux.sh.1
prog-${HAVE_TMUX} += examples-tmux.sh.2
prog-${HAVE_TMUX} += examples-tmux.sh.3

prog-${HAVE_TMUX} += examples-tmux.sh.11
prog-${HAVE_TMUX} += examples-tmux.sh.12
prog-${HAVE_TMUX} += examples-tmux.sh.13
prog-${HAVE_TMUX} += examples-tmux.sh.14

PROG_ARGS_examples-tmux.sh.1 := --stdin-data-format line-separator-newline
PROG_ARGS_examples-tmux.sh.2 := --stdin-data-format line-separator-semicolon
PROG_ARGS_examples-tmux.sh.3 := --stdin-data-format scatter-no-separator

PROG_ARGS_examples-tmux.sh.11 := --vertical-plotting
PROG_ARGS_examples-tmux.sh.12 := --vertical-plotting ${PROG_ARGS_examples-tmux.sh.1}
PROG_ARGS_examples-tmux.sh.13 := --vertical-plotting ${PROG_ARGS_examples-tmux.sh.2}
PROG_ARGS_examples-tmux.sh.14 := --vertical-plotting ${PROG_ARGS_examples-tmux.sh.3}

post-y += build/plotcake
post-y += id-handler-glibc
