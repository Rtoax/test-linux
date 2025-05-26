# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

TARGETS := fakeinit

IMAGES := initrd.img

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -static
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS} ${IMAGES}

%.img:
	${Q}./build-initrd.sh

fakeinit: fakeinit.o

%.o: %.c
	@echo -e " CC \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e " LD \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^)

clean:
	@echo -e " CLEAN \033[1;32m$(TARGETS) ${IMAGES}\033[m"
	${Q}rm -rf ${TARGETS} ${IMAGES} *.o *.d rootfs* *.log *.img
