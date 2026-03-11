target-y += getutent getutid
target-y += getutline pututline
target-y += utmpname
target-y += updwtmp
target-y += setutent endutent
target-y += login logwtmp
target-y += login_tty

getutent-objs := utmp_helpers.o
getutid-objs := utmp_helpers.o
getutline-objs := utmp_helpers.o
pututline-objs := utmp_helpers.o
updwtmp-objs := utmp_helpers.o

LDFLAGS += -lutil
