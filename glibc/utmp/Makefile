include ../../tlbuild.mk

TARGETS :=
TARGETS += getutent getutid
TARGETS += getutline pututline
TARGETS += utmpname
TARGETS += updwtmp
TARGETS += setutent endutent
TARGETS += login logwtmp
TARGETS += login_tty

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -lutil

LDFLAGS :=

LDFLAGS += -lutil

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

utmp_helpers.o: utmp_helpers.h

getutent: getutent.o utmp_helpers.o
getutid: getutid.o utmp_helpers.o
getutline: getutline.o utmp_helpers.o
pututline: pututline.o utmp_helpers.o
utmpname: utmpname.o
updwtmp: updwtmp.o utmp_helpers.o
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
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
