SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += getutent getutid
TARGETS += getutline pututline
TARGETS += utmpname
TARGETS += updwtmp
TARGETS += setutent endutent
TARGETS += login logwtmp
TARGETS += login_tty

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -lutil

LDFLAGS :=
LDLIBS :=

LDFLAGS += -lutil

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

getutent: getutent.o helpers.o
getutid: getutid.o helpers.o
getutline: getutline.o helpers.o
pututline: pututline.o helpers.o
utmpname: utmpname.o
updwtmp: updwtmp.o helpers.o
setutent: setutent.o
endutent: endutent.o
login: login.o
logwtmp: logwtmp.o
login_tty: login_tty.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
