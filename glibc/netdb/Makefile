SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


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

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=


.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

gai_strerror: gai_strerror.o
getaddrinfo: getaddrinfo.o
gethostbyaddr: gethostbyaddr.o helpers.o
gethostbyname: gethostbyname.o helpers.o
gethostbyname_r: gethostbyname_r.o helpers.o
gethostbyname-2: gethostbyname-2.o
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
herror: herror.o
getnameinfo: getnameinfo.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

