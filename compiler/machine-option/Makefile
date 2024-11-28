SHELL = bash

TARGETS :=
TARGETS += march-native
TARGETS += mbranch-protection

ifeq ($(shell uname -m),aarch64)
  TARGETS += march-armv8.3-a
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

include ../../scripts/check_compiler_option.mk

pac-ret := $(findstring 1,$(call check_compiler_option,$(CC),-mbranch-protection=pac-ret))

ifeq (${pac-ret},1)
  CFLAGS_mbranch-protection := -mbranch-protection=pac-ret
else
  $(warning "$(CC) not support -mbranch-protection=pac-ret")
endif


CFLAGS_march-armv8.3-a := -march=armv8.3-a

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

include ../../tlbuild.mk

# FIXME: HygonGenuine not support x86-64
ifneq ($(CPU_VENDOR_ID),HygonGenuine)
  CFLAGS_march-native := -march=native
else
  $(warning CPU Vendor ID: ${CPU_VENDOR_ID})
endif

march-native: march-native.o
march-armv8.3-a: march-armv8.3-a.o
mbranch-protection: mbranch-protection.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	@$(CC) $(CFLAGS) -S $(<) -o $(<:.c=-nof.s) -Wno-error

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s

info:
	@${SHELL} info.sh
