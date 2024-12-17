# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += helloworld
TARGETS += march-native
TARGETS += mbranch-protection

ifeq ($(shell uname -m),aarch64)
  TARGETS += march-armv8.3-a
endif

# FIXME: aarch64 seems like don't support -mfentry
ifeq ($(shell uname -m),x86_64)
  TARGETS += mfentry
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

include ../../compiler/compiler.mk

pac-ret := $(findstring 1,$(call check_compiler_option,$(CC),-mbranch-protection=pac-ret))

ifeq (${pac-ret},1)
  CFLAGS_mbranch-protection := -mbranch-protection=pac-ret
else
  $(warning "$(CC) not support -mbranch-protection=pac-ret")
endif


CFLAGS_march-armv8.3-a := -march=armv8.3-a
CFLAGS_mfentry := -pg -mfentry

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

include ../../tlbuild.mk

# FIXME: HygonGenuine not support x86-64
ifneq ($(CPU_VENDOR_ID),HygonGenuine)
  CFLAGS_march-native := -march=native
else
  $(warning CPU Vendor ID: ${CPU_VENDOR_ID})
endif

helloworld: helloworld.o
march-native: march-native.o
march-armv8.3-a: march-armv8.3-a.o
mbranch-protection: mbranch-protection.o
mfentry: mfentry.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	${Q}$(CC) $(CFLAGS) -S $(<) -o $(<:.c=-nof.s) -Wno-error

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.s

info:
	@${SHELL} info.sh
