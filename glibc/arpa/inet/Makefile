TARGETS :=
TARGETS += htonl
TARGETS += htons
TARGETS += ntohl
TARGETS += ntohs
TARGETS += inet_ntoa
TARGETS += inet_ntop
TARGETS += inet_pton
TARGETS += inet_aton
TARGETS += inet_addr
TARGETS += inet_network

CFLAGS := -Werror -Wall -D_GNU_SOURCE
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
