TARGETS :=
TARGETS += gai_strerror
TARGETS += getaddrinfo
TARGETS += gethostbyaddr
TARGETS += gethostbyname gethostbyname_r
TARGETS += getservbyport getservbyname
TARGETS += hstrerror
TARGETS += setservent
TARGETS += setnetent
TARGETS += sethostent
TARGETS += innetgr
TARGETS += getprotoent getprotobyname getprotobynumber
TARGETS += getnetbyname
TARGETS += getipnodebyname

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
gethostbyname_r: gethostbyname_r.o helpers.o
getservbyport: getservbyport.o helpers.o
getservbyname: getservbyname.o helpers.o
hstrerror: hstrerror.o
setservent: setservent.o
setnetent: setnetent.o helpers.o
sethostent: sethostent.o
innetgr: innetgr.o
getprotoent: getprotoent.o helpers.o
getprotobynumber: getprotobynumber.o helpers.o
getprotobyname: getprotobyname.o helpers.o
getnetbyname: getnetbyname.o helpers.o
getipnodebyname: getipnodebyname.o

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
