# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk
include qcow2.mk

TARGETS :=
QCOW2S :=

TARGETS += qcow2
QCOW2S += a.qcow2

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS} ${QCOW2S}
	@echo -e " \033[1;33m Done \033[m"

qcow2.o: qcow2.h
qcow2: qcow2.o

%.qcow2:
	@echo -e "  QCOW2 \033[1m$(@)\033[m"
	$(call create_qcow2,$(@),1G)

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(QCOW2S)\033[m"
	${Q}rm -f ${TARGETS} ${QCOW2S} *.o
