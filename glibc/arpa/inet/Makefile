target-y :=
target-y += htonl
target-y += htons
target-y += ntohl
target-y += ntohs
target-y += inet_ntoa
target-y += inet_ntop
target-y += inet_pton
target-y += inet_aton
target-y += inet_addr
target-y += inet_network

CFLAGS :=
CFLAGS += -pthread

include ../../../template/main.mk

htonl: htonl.o
htons: htons.o
ntohl: ntohl.o
ntohs: ntohs.o
inet_ntoa: inet_ntoa.o
inet_pton: inet_pton.o
inet_ntop: inet_ntop.o
inet_aton: inet_aton.o
inet_addr: inet_addr.o
inet_network: inet_network.o
