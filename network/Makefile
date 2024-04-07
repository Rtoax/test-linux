TARGETS :=
TARGETS += ethtool
TARGETS += tcpdump

ethtool: ethtool.o
tcpdump: tcpdump.o

build: ${TARGETS}

clean:
	rm -f ${TARGETS} *.o
