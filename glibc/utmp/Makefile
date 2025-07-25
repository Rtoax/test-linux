targets :=
targets += getutent getutid
targets += getutline pututline
targets += utmpname
targets += updwtmp
targets += setutent endutent
targets += login logwtmp
targets += login_tty

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
