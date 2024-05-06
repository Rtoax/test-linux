TARGETS :=
TARGETS += ethtool
TARGETS += tcpdump

CC = gcc

ethtool: ethtool.o
tcpdump: tcpdump.o

.PHONY: build
build: ${TARGETS}

.PHONY: clean
clean:
	rm -f ${TARGETS} *.o
