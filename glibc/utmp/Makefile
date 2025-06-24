TARGETS :=
TARGETS += getutent getutid
TARGETS += getutline pututline
TARGETS += utmpname
TARGETS += updwtmp
TARGETS += setutent endutent
TARGETS += login logwtmp
TARGETS += login_tty

CFLAGS :=
CFLAGS += -lutil

LDFLAGS :=
LDFLAGS += -lutil

include ../../template/main.mk

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
