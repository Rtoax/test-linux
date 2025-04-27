include ../../tlbuild.mk

TARGETS :=
TARGETS += gai_strerror
TARGETS += getaddrinfo
TARGETS += gethostbyaddr
TARGETS += gethostbyname gethostbyname_r gethostbyname-2
TARGETS += getservbyport getservbyname
TARGETS += hstrerror
TARGETS += setservent
TARGETS += setnetent
TARGETS += sethostent
TARGETS += innetgr
TARGETS += getprotoent getprotobyname getprotobynumber
TARGETS += getnetbyname
TARGETS += getipnodebyname
TARGETS += herror
TARGETS += getnameinfo

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=


.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

netdb_helpers.o: netdb_helpers.h

gai_strerror: gai_strerror.o
getaddrinfo: getaddrinfo.o
gethostbyaddr: gethostbyaddr.o netdb_helpers.o
gethostbyname: gethostbyname.o netdb_helpers.o
gethostbyname_r: gethostbyname_r.o netdb_helpers.o
gethostbyname-2: gethostbyname-2.o
getservbyport: getservbyport.o netdb_helpers.o
getservbyname: getservbyname.o netdb_helpers.o
hstrerror: hstrerror.o
setservent: setservent.o
setnetent: setnetent.o netdb_helpers.o
sethostent: sethostent.o
innetgr: innetgr.o
getprotoent: getprotoent.o netdb_helpers.o
getprotobynumber: getprotobynumber.o netdb_helpers.o
getprotobyname: getprotobyname.o netdb_helpers.o
getnetbyname: getnetbyname.o netdb_helpers.o
getipnodebyname: getipnodebyname.o
herror: herror.o
getnameinfo: getnameinfo.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

