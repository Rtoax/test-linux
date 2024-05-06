TARGETS :=
TARGETS += ethtool
TARGETS += tcpdump
TARGETS += ifconfig

CC = gcc

.PHONY: build
build: ${TARGETS}

ethtool: ethtool.o
tcpdump: tcpdump.o
ifconfig: ifconfig.o

.PHONY: clean
clean:
	rm -f ${TARGETS} *.o
