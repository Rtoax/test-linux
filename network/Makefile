# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

sub-dir :=
sub-dir += icmp
sub-dir += nic

TARGETS :=
TARGETS += ethtool
TARGETS += tcpdump
TARGETS += ifconfig
TARGETS += ping

CC := gcc

include ../template/subdir-header.mk

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	${Q}./interface.sh
	@echo -e " \033[1;33m Done \033[m"

ethtool: ethtool.o
tcpdump: tcpdump.o
ifconfig: ifconfig.o
ping: ping.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

include ../template/subdir-footer.mk
