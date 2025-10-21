target-y := gai_strerror
target-y += getaddrinfo
target-y += gethostbyaddr
target-y += gethostbyname gethostbyname_r gethostbyname-2
target-y += getservbyport getservbyname
target-y += hstrerror
target-y += setservent
target-y += setnetent
target-y += sethostent
target-y += innetgr
target-y += getprotoent getprotobyname getprotobynumber
target-y += getnetbyname
target-y += getipnodebyname
target-y += herror
target-y += getnameinfo

include ../../template/main.mk

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
