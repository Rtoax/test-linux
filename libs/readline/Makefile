READLINE_HDR = /usr/include/readline/readline.h

target-y += rlversion
target-y += rltest

ifeq ($(wildcard $(READLINE_HDR)),)
  $(warning "WARNING: Must install readline development header")
  target-y :=
endif

ifneq ($(wildcard $(READLINE_HDR)),)
  LDFLAGS += -lreadline -lutil -ltermcap -lhistory
endif

include main.mk
