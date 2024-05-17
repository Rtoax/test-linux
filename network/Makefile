TARGETS :=
TARGETS += ethtool
TARGETS += tcpdump
TARGETS += ifconfig
TARGETS += ping

CC = gcc

.PHONY: build
build: ${TARGETS}

ethtool: ethtool.o
tcpdump: tcpdump.o
ifconfig: ifconfig.o
ping: ping.o

.PHONY: clean
clean:
	rm -f ${TARGETS} *.o
