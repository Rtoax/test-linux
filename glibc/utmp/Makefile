TARGETS :=
TARGETS += getutent getutid
TARGETS += utmpname
TARGETS += updwtmp
TARGETS += setutent endutent

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=


.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

getutent: getutent.o
getutid: getutid.o
utmpname: utmpname.o
updwtmp: updwtmp.o
setutent: setutent.o
endutent: endutent.o

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
