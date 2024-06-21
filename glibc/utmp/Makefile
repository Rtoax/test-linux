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
	@echo
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

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
