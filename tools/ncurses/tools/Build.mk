include file.mk
include json-c.mk
include ncurses.mk

target-y += plotcake

prog-y += examples.sh
prog-$(call fexist,/usr/bin/expect) += examples.exp

$(foreach obj, plotcake keyboard file loadavg lgroup line plot ram stdin \
	  ltypes utils axis, \
  $(eval plotcake-objs += ${obj}.o))

CFLAGS += ${json-c-cflags}

LDFLAGS += -lm
LDFLAGS += ${json-c-ldflags}
LDFLAGS += ${ncurses-ldflags}
