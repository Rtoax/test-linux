TARGETS :=
TARGETS += gai_strerror
TARGETS += getaddrinfo
TARGETS += gethostbyaddr
TARGETS += gethostbyname
TARGETS += getservbyport getservbyname
TARGETS += hstrerror
TARGETS += setservent
TARGETS += setnetent
TARGETS += sethostent
TARGETS += innetgr

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=


.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

gai_strerror: gai_strerror.o
getaddrinfo: getaddrinfo.o
gethostbyaddr: gethostbyaddr.o helpers.o
gethostbyname: gethostbyname.o helpers.o
getservbyport: getservbyport.o helpers.o
getservbyname: getservbyname.o helpers.o
hstrerror: hstrerror.o
setservent: setservent.o
setnetent: setnetent.o
sethostent: sethostent.o
innetgr: innetgr.o

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
