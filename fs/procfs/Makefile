# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

sub-dir := process

TARGETS :=
TARGETS += proc_examples
TARGETS += self thread-self
TARGETS += auxv
TARGETS += stat
TARGETS += statm
TARGETS += status
TARGETS += uptime

TARGETS_LIBA := libtest-linux-procfs.a

CC := gcc

CFLAGS :=
CFLAGS += -DDEBUG -O0 -g

include ../../elf/pie.mk
include ../../template/subdir-header.mk

.PHONY: build
build: ${TARGETS} ${TARGETS_LIBA} $(sub-dir-build)
	$(Q)./mounts.sh
	${Q}./proc_examples
	@echo -e " \033[1;33m Done \033[m"

include procfs-lib-target.mk

proc_examples: proc_examples.o proc_helpers.o
proc_examples.o: proc_helpers.h
proc_helpers.o: proc_helpers.h
self: self.o
thread-self: thread-self.o
auxv: auxv.o
stat: stat.o
statm: statm.o
status: status.o
uptime: uptime.o

libtest-linux-procfs.a: proc_helpers.a.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

include ../../template/target-liba.mk

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	${Q}./self

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_LIBA} *.o *.d

include ../../template/subdir-footer.mk
