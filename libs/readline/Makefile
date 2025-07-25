READLINE_HDR = /usr/include/readline/readline.h

targets :=
targets += rlversion
targets += rltest

ifeq ($(wildcard $(READLINE_HDR)),)
  $(warning "WARNING: Must install readline development header")
  targets :=
endif

CFLAGS :=

ifneq ($(wildcard $(READLINE_HDR)),)
  LDFLAGS += -lreadline -lutil -ltermcap -lhistory
endif

include ../../template/main.mk

rlversion: rlversion.o
rltest: rltest.o
